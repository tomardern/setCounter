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

#include "newset.h"

static Window window;


void newset_init_settings_window()
{
    window_init(&window, "Timer Settings");
    window_set_background_color(&window, GColorWhite);



}

void display_newset()
{

    newset_init_settings_window();

    window_stack_push(&window, true);
}