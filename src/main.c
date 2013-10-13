/*
 * Sample
 * Copyright (C) 2013 Dirk Mika
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "settings.h"
#include "home.h"

#define MY_UUID { 0x62, 0x99, 0x77, 0xd3, 0x3d, 0xfe, 0x43, 0xbb, 0xa6, 0x5d, 0x1a, 0x3a, 0x5b, 0x9c, 0x0a, 0x15 }
PBL_APP_INFO(MY_UUID,
             "Sample", "Dirk Mika",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_STANDARD_APP);


// Global vars
AppContextRef app;
Window window;
ActionBarLayer action_bar_layer;


// Some various bitmaps for actionbar-buttons
HeapBitmap button_image_up;
HeapBitmap button_image_down;
HeapBitmap button_image_setup;

SampleSettings sample_settings  = {
    false
};

SampleHome sample_home = {
	false
};

void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {
    (void)recognizer;
    (void)window;

    display_settings(&sample_settings);


    // As another windows is pushed, the button-release is not handler by the actionbar. We need to unselect the button manually
    action_bar_layer.is_highlighted = 0;
}

void select_long_release_handler(ClickRecognizerRef recognizer, Window *window) {
    (void)recognizer;
    (void)window;
}

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
    (void)recognizer;
    (void)window;
}

void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
    (void)recognizer;
    (void)window;
}

void click_config_provider(ClickConfig **config, Window *window) {
    (void)window;

    config[BUTTON_ID_SELECT]->long_click.handler = (ClickHandler) select_long_click_handler;
    config[BUTTON_ID_SELECT]->long_click.release_handler = (ClickHandler) select_long_release_handler;

    config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
    config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

    config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
    config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;

}


// WindowHandlers
void handle_main_appear(Window *window)
{
    // We need to add the action_bar when the main-window appears. If we do this in handle_init it picks up wrong window-bounds and the size doesn't fit.
    //action_bar_layer_add_to_window(&action_bar_layer, window);
}

void handle_main_disappear(Window *window)
{
    // Since we add the layer on each appear, we remove it on each disappear.
    //action_bar_layer_remove_from_window(&action_bar_layer);
}



void handle_init(AppContextRef ctx)
{
    app = ctx;

    window_init(&window, "Sample");
    window_set_window_handlers(&window, (WindowHandlers) {
        .appear = (WindowHandler)handle_main_appear,
        .disappear = (WindowHandler)handle_main_disappear
    });

    // Init resources
    resource_init_current_app(&APP_RESOURCES);

    // Load some bitmaps
    //heap_bitmap_init(&button_image_up, RESOURCE_ID_IMAGE_BUTTON_UP);
    //heap_bitmap_init(&button_image_down, RESOURCE_ID_IMAGE_BUTTON_DOWN);
    //heap_bitmap_init(&button_image_setup, RESOURCE_ID_IMAGE_BUTTON_SETUP);

    //action_bar_layer_init(&action_bar_layer);
    //action_bar_layer_set_click_config_provider(&action_bar_layer, (ClickConfigProvider) click_config_provider);
    //action_bar_layer_set_icon(&action_bar_layer, BUTTON_ID_UP, &button_image_up.bmp);
    //action_bar_layer_set_icon(&action_bar_layer, BUTTON_ID_SELECT, &button_image_setup.bmp);
    //action_bar_layer_set_icon(&action_bar_layer, BUTTON_ID_DOWN, &button_image_down.bmp);

    //window_stack_push(&window, true);

    //Display the settings straight-away
    display_home(&sample_home);
}

void handle_init_old(AppContextRef ctx)
{
    app = ctx;

    window_init(&window, "Sample");
    window_set_window_handlers(&window, (WindowHandlers) {
        .appear = (WindowHandler)handle_main_appear,
        .disappear = (WindowHandler)handle_main_disappear
    });

    // Init resources
    resource_init_current_app(&APP_RESOURCES);

    // Load some bitmaps
    heap_bitmap_init(&button_image_up, RESOURCE_ID_IMAGE_BUTTON_UP);
    heap_bitmap_init(&button_image_down, RESOURCE_ID_IMAGE_BUTTON_DOWN);
    heap_bitmap_init(&button_image_setup, RESOURCE_ID_IMAGE_BUTTON_SETUP);

    action_bar_layer_init(&action_bar_layer);
    action_bar_layer_set_click_config_provider(&action_bar_layer, (ClickConfigProvider) click_config_provider);
    action_bar_layer_set_icon(&action_bar_layer, BUTTON_ID_UP, &button_image_up.bmp);
    action_bar_layer_set_icon(&action_bar_layer, BUTTON_ID_SELECT, &button_image_setup.bmp);
    action_bar_layer_set_icon(&action_bar_layer, BUTTON_ID_DOWN, &button_image_down.bmp);

    window_stack_push(&window, true);

	//Display the settings straight-away
	display_home(&sample_home);
}

void handle_deinit(AppContextRef ctx)
{
    heap_bitmap_deinit(&button_image_up);
    heap_bitmap_deinit(&button_image_down);
    heap_bitmap_deinit(&button_image_setup);

    window_deinit(&window);
}




void pbl_main(void *params)
{
    PebbleAppHandlers handlers = {
        .init_handler = &handle_init,
        .deinit_handler = &handle_deinit
    };
    app_event_loop(params, &handlers);
}