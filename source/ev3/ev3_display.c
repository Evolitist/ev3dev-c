#include "ev3_display.h"

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <locale.h>
#include <wchar.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "linux/kd.h"
#include "system.8x16.h"

#define LCD_X_SIZE		178
#define LCD_Y_SIZE		128
#define LCD_LINE_SIZE		712
#define LCD_FB_LENGTH		91136

int fb_file = 0, vt_file = 0;
uint8_t *fb_ptr = NULL, old_fb[LCD_FB_LENGTH];

int ev3_display_init()
{
	fb_file = open("/dev/fb0", O_RDWR);
	if(!fb_file) return 1;
	fb_ptr = (uint8_t*)mmap(0, LCD_FB_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fb_file, 0);
	if((int)fb_ptr == -1) return 1;
	vt_file = open("/dev/tty", O_RDONLY);
	if(!vt_file) return 1;
	ioctl(vt_file, KDSETMODE, KD_GRAPHICS);
	setlocale(LC_ALL, "en_US.utf8");
	memcpy(old_fb, fb_ptr, LCD_FB_LENGTH);
	memset(fb_ptr, 255, LCD_FB_LENGTH);
	return 0;
}

void display_clear()
{
	memset(fb_ptr, 255, LCD_FB_LENGTH);
}

void display_draw_pixel(int x, int y, bool fill)
{
	if(x < 0 || x >= LCD_X_SIZE || y < 0 || y >= LCD_Y_SIZE) return;
	int trgt = y * LCD_LINE_SIZE + (x * 4);
	memset(fb_ptr + trgt, fill ? 0 : 255, 4);
}

void display_clear_text_line(uint8_t line)
{
	if(line >= 8) return;
	int sl = line * 16 * LCD_LINE_SIZE;
	memset(fb_ptr + sl, 255, LCD_LINE_SIZE);
}

void draw_char_at(int _sl, char toDraw)
{
	int sl = _sl;
	char t = toDraw ^ 255, st;
	while(t != 0)
	{
		st = (t & 1) * 255;
		memset(fb_ptr + sl, st, 4);
		sl += 4;
		t = t >> 1;
	}
}

void draw_big_char_at(int _sl, char toDraw)
{
	int sl = _sl;
	char t = toDraw ^ 255, st;
	while(t != 0)
	{
		st = (t & 1) * 255;
		memset(fb_ptr + sl, st, 8);
		memset(fb_ptr + sl + LCD_LINE_SIZE, st, 8);
		sl += 8;
		t = t >> 1;
	}
}

void display_draw_text_line(uint8_t line, const char *__str, ...)
{
	if(line >= 8) return;
	char _str[45];
	va_list vl;
	va_start(vl, __str);
	vsnprintf(_str, 44, __str, vl);
	va_end(vl);
	wchar_t str[23];
	mbstowcs(str, _str, 22);
	int sl = line * 16 * LCD_LINE_SIZE;
	bool wipe;
	for(int i = 0; i < 16; i++)
	{
		wipe = false;
		for(int j = 0; j < 22; j++)
		{
			if(str[j] == 0) wipe = true;
			if(wipe)
			{
				memset(fb_ptr + sl, 255, LCD_LINE_SIZE - (sl % LCD_LINE_SIZE));
				break;
			}
			else
			{
				draw_char_at(sl, get_char((int)str[j])[i]);
				sl += 32;
				//memset(fb_ptr + sl, get_char((int)str[j])[i], 1);
			}
			//sl += 32;
		}
		sl += LCD_LINE_SIZE - (sl % LCD_LINE_SIZE);
	}
}

void display_draw_big_text_line(uint8_t line, const char *__str, ...)
{
	if(line >= 7) return;
	char _str[23];
	va_list vl;
	va_start(vl, __str);
	vsnprintf(_str, 22, __str, vl);
	va_end(vl);
	wchar_t str[12];
	mbstowcs(str, _str, 11);
	int sl = line * 16 * LCD_LINE_SIZE;
	bool wipe;
	for(int i = 0; i < 16; i+=2)
	{
		wipe = false;
		for(int j = 0; j < 11; j++)
		{
			if(str[j] == 0) wipe = true;
			if(wipe)
			{
				memset(fb_ptr + sl, 255, LCD_LINE_SIZE - (sl % LCD_LINE_SIZE));
				memset(fb_ptr + sl + LCD_LINE_SIZE, 255, LCD_LINE_SIZE - (sl % LCD_LINE_SIZE));
				break;
			}
			else
			{
				draw_big_char_at(sl, get_char((int)str[j])[i]);
				sl += 64;
				//memset(fb_ptr + sl, get_char((int)str[j])[i], 1);
			}
			//sl += 32;
		}
		sl += LCD_LINE_SIZE - (sl % LCD_LINE_SIZE) + LCD_LINE_SIZE;
	}
}

void display_draw_centered_text_line(uint8_t line, const char *__str, ...)
{
	if(line >= 8) return;
	char _str[45];
	va_list vl;
	va_start(vl, __str);
	vsnprintf(_str, 44, __str, vl);
	va_end(vl);
	wchar_t str[23];
	mbstowcs(str, _str, 22);
	int wsl = wcslen(str);
	int sl = line * 16 * LCD_LINE_SIZE, sp = sl + ((22 - wsl) / 2 * 32);
	if(wsl % 2 != 0)
	{
		str[wsl] = L' ';
		str[wsl + 1] = 0;
		wsl++;
	}
	for(int i = 0; i < 16; i++)
	{
		memset(fb_ptr + sl, 255, sp - sl);
		//draw_char_at(sp, get_char((int)str[0])[i]);
		for(int j = 0; j < wsl; j++)
		{
			draw_char_at(sp + j * 32, get_char((int)str[j])[i]);
		}
		memset(fb_ptr + sp + wsl * 32, 255, LCD_LINE_SIZE - ((sp + wsl * 32) % LCD_LINE_SIZE));
		sl += LCD_LINE_SIZE;
		sp += LCD_LINE_SIZE;
	}
}

void display_draw_centered_big_text_line(uint8_t line, const char *__str, ...)
{
	if(line >= 7) return;
	char _str[23];
	va_list vl;
	va_start(vl, __str);
	vsnprintf(_str, 22, __str, vl);
	va_end(vl);
	wchar_t str[12];
	mbstowcs(str, _str, 11);
	int wsl = wcslen(str);
	int sl = line * 16 * LCD_LINE_SIZE, sp = sl + ((11 - wsl) / 2 * 32);
	if(wsl % 2 != 0)
	{
		str[wsl] = L' ';
		str[wsl + 1] = 0;
		wsl++;
	}
	for(int i = 0; i < 16; i++)
	{
		memset(fb_ptr + sl, 255, sp - sl);
		memset(fb_ptr + sl + LCD_LINE_SIZE, 255, sp - sl);
		//draw_char_at(sp, get_char((int)str[0])[i]);
		for(int j = 0; j < wsl; j++)
		{
			draw_big_char_at(sp + j * 64, get_char((int)str[j])[i]);
		}
		memset(fb_ptr + sp + wsl * 64, 255, LCD_LINE_SIZE - ((sp + wsl * 32) % LCD_LINE_SIZE));
		memset(fb_ptr + sp + wsl * 64 + LCD_LINE_SIZE, 255, LCD_LINE_SIZE - ((sp + wsl * 32) % LCD_LINE_SIZE));
		sl += LCD_LINE_SIZE + LCD_LINE_SIZE;
		sp += LCD_LINE_SIZE + LCD_LINE_SIZE;
	}
}

void display_draw_string(uint8_t line, const char *__str, ...)
{
	if(line >= 8) return;
	char _str[45];
	va_list vl;
	va_start(vl, __str);
	vsnprintf(_str, 44, __str, vl);
	va_end(vl);
	wchar_t str[23];
	mbstowcs(str, _str, 22);
	int sl = line * 16 * LCD_LINE_SIZE;
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 22; j++)
		{
			if(str[j] == 0) break;
			draw_char_at(sl, get_char((int)str[j])[i]);
			sl += 32;
		}
		sl += LCD_LINE_SIZE - (sl % LCD_LINE_SIZE);
	}
}

void ev3_display_uninit()
{
	memcpy(fb_ptr, old_fb, LCD_FB_LENGTH);
	munmap(fb_ptr, LCD_FB_LENGTH);
	close(fb_file);
	ioctl(vt_file, KDSETMODE, KD_TEXT);
	close(vt_file);
}
