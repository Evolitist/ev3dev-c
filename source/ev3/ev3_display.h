#ifndef EV3_DISPLAY_H
#define EV3_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

int ev3_display_init();
void display_clear();
void display_draw_pixel(int x, int y, bool fill);
void display_clear_text_line(uint8_t line);
void display_draw_text_line(uint8_t line, const char *_str, ...);
void display_draw_big_text_line(uint8_t line, const char *_str, ...);
void display_draw_centered_text_line(uint8_t line, const char *__str, ...);
void display_draw_centered_big_text_line(uint8_t line, const char *__str, ...);
void display_draw_string(uint8_t line, const char *__str, ...);
void display_draw_big_string(uint8_t line, const char *__str, ...);
void ev3_display_uninit();

#ifdef __cplusplus
}
#endif

#endif

