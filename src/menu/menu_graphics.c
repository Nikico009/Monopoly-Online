#include "raylib.h"
#include <stdio.h>
#include "graphics.h"
#include "menu_graphics.h"

void init_window(Window* window) {
    InitWindow(window->width, window->height, "Monopoly Online");
    SetExitKey(KEY_NULL);
    SetTargetFPS(window->target_fps);
}

void window_loop(Window* window) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
}

void draw_button(int x, int y, int width, int height, const char* text) {
    DrawRectangle(x, y, width, height, LIGHTGRAY);
    DrawText(text, x + 10, y + 10, 20, BLACK);
}

void draw_title(const char* title) {
    DrawText(title, TITLE_X, TITLE_Y, 40, DARKGRAY);
}

void draw_main_menu() {
    draw_title("MONOPOLY ONLINE");
    draw_button(CREATE_GAME_BUTTON_X, CREATE_GAME_BUTTON_Y,
                CREATE_GAME_BUTTON_WIDTH, CREATE_GAME_BUTTON_HEIGHT, "Create Game");
    draw_button(JOIN_GAME_BUTTON_X, JOIN_GAME_BUTTON_Y,
                JOIN_GAME_BUTTON_WIDTH, JOIN_GAME_BUTTON_HEIGHT, "Join Game");
    draw_button(SETTINGS_BUTTON_X, SETTINGS_BUTTON_Y,
                SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT, "Settings");
    draw_button(EXIT_BUTTON_X, EXIT_BUTTON_Y,
                EXIT_BUTTON_WIDTH, EXIT_BUTTON_HEIGHT, "Exit");
}

void draw_create_game_menu() {
    draw_title("Create Game");
    DrawText("Press ESC to return to the main menu", 200, 520, 20, DARKGRAY);
}

void draw_join_game_menu() {
    draw_title("Join Game");
    DrawText("Press ESC to return to the main menu", 200, 520, 20, DARKGRAY);
}

void draw_settings_menu(int screen_width, int screen_height, bool is_fullscreen) {
    draw_title("Settings");
    draw_button(CHANGE_RESOLUTION_BUTTON_X, CHANGE_RESOLUTION_BUTTON_Y,
                CHANGE_RESOLUTION_BUTTON_WIDTH, CHANGE_RESOLUTION_BUTTON_HEIGHT, "Change Resolution");
    DrawRectangleLines(RESOLUTION_DISPLAY_X, RESOLUTION_DISPLAY_Y,
                       RESOLUTION_DISPLAY_WIDTH, RESOLUTION_DISPLAY_HEIGHT, DARKGRAY);

    char resolution_text[32];
    snprintf(resolution_text, sizeof(resolution_text), "%d x %d px", screen_width, screen_height);
    int text_width = MeasureText(resolution_text, 20);
    DrawText(resolution_text,
             RESOLUTION_DISPLAY_X + (RESOLUTION_DISPLAY_WIDTH - text_width) / 2,
             RESOLUTION_DISPLAY_Y + (RESOLUTION_DISPLAY_HEIGHT - 20) / 2,
             20, DARKGRAY);

    draw_button(DISPLAY_MODE_BUTTON_X, DISPLAY_MODE_BUTTON_Y,
                DISPLAY_MODE_BUTTON_WIDTH, DISPLAY_MODE_BUTTON_HEIGHT,
                is_fullscreen ? "Windowed" : "Fullscreen");
    DrawText("Press ESC to return to the main menu", 200, 520, 20, DARKGRAY);
}