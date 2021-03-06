//
//  settings.c
//
//
//  Created by Dirk Mika on 08.05.13.
//
//
//This is a test of the pull system and again and again!

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "home.h"
#include "newset.h" //This needs to know about the newset, so that it can understand what to run

static Window window;
static SimpleMenuLayer homeMenu_layer;
static SimpleMenuSection homeMenu_sections[2];      // Two sections
static SimpleMenuItem homeMenu_section0_items[2];   // Section 0 (Some settings...) with one entry
static SimpleMenuItem homeMenu_section1_items[2];   // Section 1 (About...) with one entry

HeapBitmap menu_icon_0_0;
HeapBitmap menu_icon_1_0;


//menu_layer_reload_data(&homeMenu_layer.menu);
void menulayer_section0_select_callback(int index, void *context)
{

    switch (index) {
        case 0:
            display_newset();
            break;
        default:
            break;
    }

}


void home_handle_appear(Window *window)
{
    scroll_layer_set_frame(&homeMenu_layer.menu.scroll_layer, window->layer.bounds);
}

void home_handle_unload(Window *window)
{
    heap_bitmap_deinit(&menu_icon_0_0);
    heap_bitmap_deinit(&menu_icon_1_0);
}

void home_init_settings_window()
{
    window_init(&window, "Timer Settings");
    window_set_background_color(&window, GColorWhite);
    window_set_window_handlers(&window, (WindowHandlers) {
        .appear = (WindowHandler)home_handle_appear,
        .unload = (WindowHandler)home_handle_unload
    });

    // Don't forget to deinit
    heap_bitmap_init(&menu_icon_0_0, RESOURCE_ID_IMAGE_SETTINGS_SAMPLE);
    heap_bitmap_init(&menu_icon_1_0, RESOURCE_ID_IMAGE_MENU_ICON);

     // Section "Settings..."
    homeMenu_section0_items[0] = (SimpleMenuItem) {
        .title = "New Set",
        .icon = &menu_icon_0_0.bmp,
        .callback = &menulayer_section0_select_callback
    };
    homeMenu_section0_items[1] = (SimpleMenuItem) {
        .title = "Sync Sets",
		.subtitle = "14:15 15/12/2003",
        .icon = NULL,
        .callback = NULL
    };

    // Header
    homeMenu_sections[0] = (SimpleMenuSection) {
        .title = NULL,
        .items = homeMenu_section0_items,
        .num_items = ARRAY_LENGTH(homeMenu_section0_items)
    };


    // Section "About..."
    homeMenu_section1_items[0] = (SimpleMenuItem) {
        .title = "Breast Stroke",
        .subtitle = "10 x 100m",
        .icon = NULL,
        .callback = NULL
    };
    homeMenu_section1_items[1] = (SimpleMenuItem) {
        .title = "Front Crawl",
        .subtitle = "5 x 100m",
        .icon = NULL,
        .callback = NULL
    };


    // Header
    homeMenu_sections[1] = (SimpleMenuSection) {
        .title = "Previous Sets",
        .items = homeMenu_section1_items,
        .num_items = ARRAY_LENGTH(homeMenu_section1_items)
    };

    simple_menu_layer_init(&homeMenu_layer, window.layer.frame, &window, homeMenu_sections, 2, NULL);
    layer_add_child(&window.layer, &homeMenu_layer.menu.scroll_layer.layer);
}

void display_home()
{

    home_init_settings_window();
    window_stack_push(&window, true);
}