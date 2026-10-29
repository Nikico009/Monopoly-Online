#ifndef MENU_LOGIC_H
#define MENU_LOGIC_H

#include "menu_graphics.h"

typedef enum {
    MENU_NO_ACTION,
    MAIN_MENU,
    CREATE_GAME_MENU,
    JOIN_GAME_MENU,
    SETTINGS_MENU,
    EXIT
} MenuState;

extern MenuState menu_state;

MenuState check_buttons_main_menu(void);

void menu_loop(Window* window);
void create_game_menu_loop(Window* window);
void join_game_menu_loop(Window* window);
void settings_menu_loop(Window* window);

#endif