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

NumberWindow numwin_duration;
NumberWindow numwin_interval;

void newset_init_settings_window()
{

    window_init(&window, "Timer Settings");
    window_set_background_color(&window, GColorWhite);

    number_window_init(number_window)


    window_stack_push((Window *) &number_window, true);


}

void display_newset()
{



  number_window_init(&numwin_duration, "Meditation Duration", (NumberWindowCallbacks) {
    .decremented = NULL,
    .incremented = NULL,
    .selected = (NumberWindowCallback) numwin_duration_selected
  }, NULL);
  number_window_set_value(&numwin_duration, 50);
  number_window_set_min(&numwin_duration, 0);
  number_window_set_max(&numwin_duration, 100);

  number_window_init(&numwin_interval, "Vibration Interval", (NumberWindowCallbacks) {
    .decremented = NULL,
    .incremented = NULL,
    .selected = (NumberWindowCallback) numwin_interval_selected
  }, NULL);
  number_window_set_value(&numwin_interval, 50);
  number_window_set_min(&numwin_interval, 0);
  number_window_set_max(&numwin_interval, 100);

  window_stack_push((Window*)&numwin_duration, true);


    //newset_init_settings_window();

    //window_stack_push(&window, true);
}

void numwin_duration_selected(struct NumberWindow *number_window, void *context) {
  //duration = number_window_get_value(&numwin_duration);
  window_stack_push((Window*)&numwin_interval, true);
}

void numwin_interval_selected(struct NumberWindow *number_window, void *context) {
  //interval = number_window_get_value(&numwin_interval);
  //window_stack_push(&window_main, true);
}