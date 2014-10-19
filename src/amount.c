#include <pebble.h>
#include "header.h"  

Window * amt_window;

static MenuLayer * menu_layer;
 
static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    //case 0:
      //menu_cell_basic_draw(ctx, cell_layer, "Custom amount", NULL, NULL);
      //break;
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "$5.00", NULL, NULL);
      break;
    case 1:
      menu_cell_basic_draw(ctx, cell_layer, "$10.00", NULL, NULL);
      break;
    case 2:
      menu_cell_basic_draw(ctx, cell_layer, "$15.00", NULL, NULL);
      break;
    case 3:
      menu_cell_basic_draw(ctx, cell_layer, "$20.00", NULL, NULL);
      break;
    case 4:
      menu_cell_basic_draw(ctx, cell_layer, "$40.00", NULL, NULL);
      break;
    case 5:
      menu_cell_basic_draw(ctx, cell_layer, "$60.00", NULL, NULL);
      break;
    case 6:
      menu_cell_basic_draw(ctx, cell_layer, "$0.10", NULL, NULL);
      break;
  }
}
 
static uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
  return 7;
}
 
static void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
   // case 0:
      //custom_init();
      //was_cust = 1;
      //break;
    case 0:
      amount = 5.0;
      camt_init();
      break;
    case 1:
      amount = 10.0;
      camt_init();
      break;
    case 2:
      amount = 15.0;
      camt_init();
      break;
    case 3:
      amount = 20.0;
      camt_init();
      break;
    case 4:
      amount = 40.0;
      camt_init();
      break;
    case 5:
      amount = 60.0;
      camt_init();
      break;
    case 6:
      amount = 0.1;
      camt_init();
      break;
  }
}

static void window_load(Window *window)
{ 
  menu_layer = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(menu_layer, amt_window);
  MenuLayerCallbacks callbacks = {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(amt_window), menu_layer_get_layer(menu_layer));
}
 
void amt_deinit()
{
  window_push--;
  menu_layer_destroy(menu_layer);
  window_destroy(amt_window);
}

static void window_unload(Window *window)
{
  amt_deinit();
}
 
void amt_init()
{
  amt_window = window_create();
  WindowHandlers handlers = {
     .load = window_load,
     .unload = window_unload,
  };
  window_set_window_handlers(amt_window, (WindowHandlers) handlers);
  window_push++;
  window_stack_push(amt_window, !was_back);
  was_back = 0;
  was_cust = 0;
}