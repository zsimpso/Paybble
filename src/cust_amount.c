/*#include <pebble.h>
#include "header.h"  

Window * custamt_window;

int button_press = 0;

static NumberWindow * num_window;
 

void down_handler_dec(){
  if(amount >= 5){
    amount -= 5;
  }
  button_press = 1;
  if(button_press){
    app_timer_register(80, down_handler_dec);
  }
}

void up_handler_dec(){
  button_press = 0;
}

void single_press_dec(){
  if(amount >= 1){
    amount--;
  }
}

static void decrement_num(){
  window_single_click_subscribe(ButtonId button_id, single_press_dec);
  window_long_click_subscribe(ButtonId button_id, 500, down_handler_dec, up_handler_dec);
}

void down_handler_inc(){
  if(amount <= 94){
    amount += 5;
  }
  button_press = 1;
  if(button_press){
    app_timer_register(80, down_handler_inc);
  }
}

void up_handler_inc(){
  button_press = 0;
}

void single_press_dec(){
  if(amount <= 98){
    amount++;
  }
}

static void increment_num(){
  window_single_click_subscribe(ButtonId button_id, single_press_inc);
  window_long_click_subscribe(ButtonId button_id, 500, down_handler_inc, up_handler_inc);
}

static void select_button(){
  camt_init();
}

static void window_load(Window *window)
{ 
  NumberWindowCallback callbacks = {
    .decremeted = decrement_num,
    .incremeted = increment_num,
    .selected = select_button,
  };
  num_window = number_window_create("Amount", callbacks);
 * menu_layer_set_click_config_onto_window(menu_layer, camt_window);
  MenuLayerCallbacks callbacks = {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(custamt_window), number_window_get_window(num_window));*
}
 
void custamt_deinit()
{
  window_push--;
  window_destroy(custamt_window);
  number_window_destroy(num_window);
}

static void window_unload(Window *window)
{
  custamt_deinit();
}
 
void custamt_init()
{
  custamt_window = window_create();
  WindowHandlers handlers = {
     .load = window_load,
     .unload = window_unload,
  };
  window_set_window_handlers(custamt_window, (WindowHandlers) handlers);
  window_push++;
  window_stack_push(custamt_window, true);
//  was_back = 0;
 // was_cust = 0;
}*/