//
//  settings.c
//
//
//  Created by Dirk Mika on 08.05.13.
//
//

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "settings.h"

static Window window;
static SimpleMenuLayer menu_layer;
static SimpleMenuSection menu_sections[2];      // Two sections
static SimpleMenuItem menu_section0_items[1];   // Section 0 (Some settings...) with one entry
static SimpleMenuItem menu_section1_items[1];   // Section 1 (About...) with one entry

HeapBitmap menu_icon_0_0;
HeapBitmap menu_icon_1_0;

SampleSettings *_sample_settings;


void menu_layer_section0_select_callback(int index, void *context)
{
    bool new_value;

    switch (index) {
        case 0:
            _sample_settings->dummy = !_sample_settings->dummy;
            menu_section0_items[0].subtitle = (_sample_settings->dummy ? "YES" : "NO");
            break;
        default:
            break;
    }
    menu_layer_reload_data(&menu_layer.menu);
}

void handle_appear(Window *window)
{
    scroll_layer_set_frame(&menu_layer.menu.scroll_layer, window->layer.bounds);
}

void handle_unload(Window *window)
{
    heap_bitmap_deinit(&menu_icon_0_0);
    heap_bitmap_deinit(&menu_icon_1_0);
}

void init_settings_window()
{
    window_init(&window, "Timer Settings");
    window_set_background_color(&window, GColorWhite);
    window_set_window_handlers(&window, (WindowHandlers) {
        .appear = (WindowHandler)handle_appear,
        .unload = (WindowHandler)handle_unload
    });

    // Don't forget to deinit
    heap_bitmap_init(&menu_icon_0_0, RESOURCE_ID_IMAGE_SETTINGS_SAMPLE);
    heap_bitmap_init(&menu_icon_1_0, RESOURCE_ID_IMAGE_MENU_ICON);

    // Section "Settings..."
    menu_section0_items[0] = (SimpleMenuItem) {
        .title = "Dummy",
        .icon = &menu_icon_0_0.bmp,
        .callback = &menu_layer_section0_select_callback
    };
    // Header
    menu_sections[0] = (SimpleMenuSection) {
        .title = "Some settings...",
        .items = menu_section0_items,
        .num_items = ARRAY_LENGTH(menu_section0_items)
    };

    // Section "About..."
    menu_section1_items[0] = (SimpleMenuItem) {
        .title = "Sample V1.0",
        .subtitle = "(C)2013 Dirk Mika",
        .icon = &menu_icon_1_0.bmp,
        .callback = NULL
    };
    // Header
    menu_sections[1] = (SimpleMenuSection) {
        .title = "About...",
        .items = menu_section1_items,
        .num_items = ARRAY_LENGTH(menu_section1_items)
    };

    simple_menu_layer_init(&menu_layer, window.layer.frame, &window, menu_sections, 2, NULL);
    layer_add_child(&window.layer, &menu_layer.menu.scroll_layer.layer);
}

void display_settings(SampleSettings *sample_settings)
{
    _sample_settings = sample_settings;

    init_settings_window();

    menu_section0_items[0].subtitle = (sample_settings->dummy ? "YES" : "NO");

    window_stack_push(&window, true);
}
