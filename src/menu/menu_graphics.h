#ifndef MENU_GRAPHICS_H
#define MENU_GRAPHICS_H



#include "raylib.h"
#include "graphics.h"

#define TITLE_X 100
#define TITLE_Y 50

typedef struct {
    int width;
    int height;
    int target_fps;
} Window;

void init_window(Window* window);

void window_loop(Window* window);

void draw_button(int x, int y, int width, int height, const char* text);

void draw_title(const char* title);

void draw_main_menu();

void draw_create_game_menu();

void draw_join_game_menu();

void draw_settings_menu(int screen_width, int screen_height, bool is_fullscreen);

#endif