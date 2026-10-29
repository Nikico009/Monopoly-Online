#include <stdio.h>
#include "raylib.h"
#include "menu.h"
#include "menu_graphics.h"

int main() {
    
    Window window = {800, 600, 60};
    init_window(&window);

    while(!WindowShouldClose() && menu_state != EXIT) {
        switch(menu_state) {
            case MAIN_MENU:
                menu_loop(&window);
                break;
            
            case CREATE_GAME_MENU:
                create_game_menu_loop(&window);
                break;

            case JOIN_GAME_MENU:
                join_game_menu_loop(&window);
                break;

            case SETTINGS_MENU:
                settings_menu_loop(&window);
                break;

            default:
                menu_state = MAIN_MENU;
                break;
        }
    }

    CloseWindow();
    return 0;
}