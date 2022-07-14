#ifndef PLATFORM_H
#define PLATFORM_H

#include "graphics.h"

typedef struct window window_t;
typedef enum { KEY_W, KEY_A, KEY_S, KEY_D, KEY_Z, KEY_C,  KEY_I, KEY_J, KEY_K, KEY_L,  KEY_Q, KEY_E, KEY_R, KEY_SPACE, KEY_NUM } keycode_t;
typedef enum { BUTTON_L, BUTTON_R, BUTTON_NUM } button_t;
typedef struct {
	void (*key_callback)(window_t* window, keycode_t key, int pressed);
	void (*button_callback)(window_t* window, button_t button, int pressed);
	void (*scroll_callback)(window_t* window, float offset);
} callbacks_t;

// platform initialization
void platform_initialize(void);
void platform_terminate(void);

// window related functions
window_t* window_create(const char* title, int width, int height, int text_width, int text_height);
void window_destroy(window_t* window);
int window_should_close(window_t* window);
void window_set_userdata(window_t* window, void* userdata);
void* window_get_userdata(window_t* window);
void window_draw_buffer(window_t* window, RenderBuffer* buffer);
void window_draw_text(window_t* window, char* text);

// input related functions 
void input_poll_events(void);
int input_key_pressed(window_t* window, keycode_t key);
int input_button_pressed(window_t* window, button_t button);
void input_query_cursor(window_t* window, float* xpos, float* ypos);
void input_set_callbacks(window_t* window, callbacks_t callbacks);

// misc platform functions
float platform_get_time(void);

#endif