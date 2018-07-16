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

#define LCD_X_SIZE     178
#define LCD_Y_SIZE     128
#define LCD_LINE_SIZE   24
#define LCD_FB_LENGTH 3072

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
	memset(fb_ptr, 0, LCD_FB_LENGTH);
	return 0;
}

void display_clear()
{
	memset(fb_ptr, 0, LCD_FB_LENGTH);
}

void display_draw_pixel(int x, int y, bool fill)
{
	if(x < 0 || x >= LCD_X_SIZE || y < 0 || y >= LCD_Y_SIZE) return;
	int trgt = y * 24 + (x >> 3);
	uint8_t b = 1 << (x & 7);
	memset(fb_ptr + trgt, fill ? fb_ptr[trgt] | b : fb_ptr[trgt] & (0xFF ^ b), 1);
}

void display_clear_text_line(uint8_t line)
{
	if(line >= 8) return;
	int sl = line * 16 * 24;
	memset(fb_ptr + sl, 0, 384);
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
	int sl = line * 16 * 24;
	bool wipe;
	for(int i = 0; i < 16; i++)
	{
		wipe = false;
		for(int j = 0; j < 22; j++)
		{
			if(str[j] == 0) wipe = true;
			if(wipe)
			{
				memset(fb_ptr + sl, 0, 24 - (sl % 24));
				break;
			}
			else memset(fb_ptr + sl, get_char((int)str[j])[i], 1);
			sl++;
		}
		sl += 24 - (sl % 24);
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
	int sl = line * 16 * 24, sp = sl + (22 - wsl) / 2;
	bool shift = (wsl % 2 != 0);
	for(int i = 0; i < 16; i++)
	{
		memset(fb_ptr + sl, 0, sp - sl);
		if(shift) memset(fb_ptr + sp, (get_char((int)str[0])[i] & 0x0F) << 4, 1);
		else memset(fb_ptr + sp, get_char((int)str[0])[i], 1);
		for(int j = 1; j < wsl; j++)
		{
			if(shift)
			{
				memset(fb_ptr + sp + j, ((get_char((int)str[j])[i] & 0x0F) << 4) + (get_char((int)str[j-1])[i] >> 4), 1);
			}
			else memset(fb_ptr + sp + j, get_char((int)str[j])[i], 1);
		}
		if(shift) memset(fb_ptr + sp + wsl, get_char((int)str[wsl - 1])[i] >> 4, 1);
		else memset(fb_ptr + sp + wsl, 0, 1);
		memset(fb_ptr + sp + wsl + 1, 0, 24 - ((sp + wsl + 1) % 24));
		sl += 24;
		sp += 24;
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
	int sl = line * 16 * 24;
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 22; j++)
		{
			if(str[j] == 0) break;
			memset(fb_ptr + sl, get_char((int)str[j])[i], 1);
			sl++;
		}
		sl += 24 - (sl % 24);
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
