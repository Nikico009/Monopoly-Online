#include "menu.h"
#include <stdio.h>
#include <stddef.h>
#include "raylib.h"
#include "graphics.h"

MenuState menu_state = MAIN_MENU;

typedef struct {
	int width;
	int height;
} ResolutionPreset;

static const ResolutionPreset resolution_presets[] = {
	{800, 600},
	{1024, 768},
	{1280, 720},
	{1280, 800},
	{1366, 768},
	{1440, 900},
	{1600, 900},
	{1920, 1080},
	{2560, 1440},
	{3840, 2160}
};

#define RESOLUTION_PRESET_COUNT (sizeof(resolution_presets) / sizeof(resolution_presets[0]))

static bool released_inside_button(int x, int y, int width, int height) {
	Vector2 mouse_position = GetMousePosition();
	Rectangle button_bounds = {(float)x, (float)y, (float)width, (float)height};

	return IsMouseButtonReleased(MOUSE_BUTTON_LEFT) &&
		   CheckCollisionPointRec(mouse_position, button_bounds);
}

MenuState check_buttons_main_menu(void) {
	if (released_inside_button(CREATE_GAME_BUTTON_X, CREATE_GAME_BUTTON_Y,
							   CREATE_GAME_BUTTON_WIDTH, CREATE_GAME_BUTTON_HEIGHT)) {
		return CREATE_GAME_MENU;
	}

	if (released_inside_button(JOIN_GAME_BUTTON_X, JOIN_GAME_BUTTON_Y,
							   JOIN_GAME_BUTTON_WIDTH, JOIN_GAME_BUTTON_HEIGHT)) {
		return JOIN_GAME_MENU;
	}

	if (released_inside_button(SETTINGS_BUTTON_X, SETTINGS_BUTTON_Y,
							   SETTINGS_BUTTON_WIDTH, SETTINGS_BUTTON_HEIGHT)) {
		return SETTINGS_MENU;
	}

	if (released_inside_button(EXIT_BUTTON_X, EXIT_BUTTON_Y,
							   EXIT_BUTTON_WIDTH, EXIT_BUTTON_HEIGHT)) {
		return EXIT;
	}

	return MENU_NO_ACTION;
}

static void cycle_resolution(Window* window) {
	size_t next_index = 0;
	for (size_t i = 0; i < RESOLUTION_PRESET_COUNT; ++i) {
		if (resolution_presets[i].width == window->width &&
			resolution_presets[i].height == window->height) {
			next_index = (i + 1) % RESOLUTION_PRESET_COUNT;
			break;
		}
	}

	window->width = resolution_presets[next_index].width;
	window->height = resolution_presets[next_index].height;
	SetWindowSize(window->width, window->height);
}

static void toggle_display_mode(Window* window) {
	if (IsWindowFullscreen()) {
		ToggleFullscreen();
		SetWindowSize(window->width, window->height);
	} else {
		window->width = GetScreenWidth();
		window->height = GetScreenHeight();
		ToggleFullscreen();
	}
}

void menu_loop(Window* window){
	(void)window;
	BeginDrawing();
	ClearBackground(RAYWHITE);
	draw_main_menu();
	EndDrawing();

    MenuState aux_state = check_buttons_main_menu();
    if (aux_state != MENU_NO_ACTION) {
        printf("Menu state: %d\n", aux_state);
        fflush(stdout);

        menu_state = aux_state;
    }
}

void create_game_menu_loop(Window* window){
	(void)window;
	BeginDrawing();
	ClearBackground(RAYWHITE);
	draw_create_game_menu();
	EndDrawing();

	if (IsKeyPressed(KEY_ESCAPE)) {
		menu_state = MAIN_MENU;
	}
}

void join_game_menu_loop(Window* window){
	(void)window;
	BeginDrawing();
	ClearBackground(RAYWHITE);
	draw_join_game_menu();
	EndDrawing();

	if (IsKeyPressed(KEY_ESCAPE)) {
		menu_state = MAIN_MENU;
	}
}

void settings_menu_loop(Window* window){
	BeginDrawing();
	ClearBackground(RAYWHITE);
	draw_settings_menu(GetScreenWidth(), GetScreenHeight(), IsWindowFullscreen());
	EndDrawing();

	if (IsKeyPressed(KEY_ESCAPE)) {
		menu_state = MAIN_MENU;
	}
	if (released_inside_button(CHANGE_RESOLUTION_BUTTON_X, CHANGE_RESOLUTION_BUTTON_Y,
							   CHANGE_RESOLUTION_BUTTON_WIDTH, CHANGE_RESOLUTION_BUTTON_HEIGHT)) {
		if (!IsWindowFullscreen()) {
			cycle_resolution(window);
		}
	}
	if (released_inside_button(DISPLAY_MODE_BUTTON_X, DISPLAY_MODE_BUTTON_Y,
							   DISPLAY_MODE_BUTTON_WIDTH, DISPLAY_MODE_BUTTON_HEIGHT)) {
		toggle_display_mode(window);
	}
}