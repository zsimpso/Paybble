#include <pebble.h>
#include "header.h"
  
Window * ven_window;

static MenuLayer * menu_layer;
 
static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "Doug", "814-574-8768", NULL);
      break;
    case 1:
      menu_cell_basic_draw(ctx, cell_layer, "Saleh", "317-908-3028", NULL);
      break;
    case 2:
      menu_cell_basic_draw(ctx, cell_layer, "Danielle", "954-849-5899", NULL);
      break;
  }
}
 
static uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
  return NUM_CONTACTS;
}
 
static void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    case 0:
      cont_name = "Doug";
      cont_num = "814-574-8768";
      break;
    case 1:
      cont_name = "Saleh";
      cont_num = "317-908-3028";
      break;
    case 02:
      cont_name = "Danielle";
      cont_num = "954-849-5899";
      break;
  }
  amt_init();
}

static void window_load(Window *window)
{ 
  menu_layer = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(menu_layer, ven_window);
  MenuLayerCallbacks callbacks = {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(ven_window), menu_layer_get_layer(menu_layer));
}
 
void ven_deinit()
{
  window_push--;
  window_destroy(ven_window);
  menu_layer_destroy(menu_layer);
}

static void window_unload(Window *window)
{
 ven_deinit();
}
 
void ven_init()
{
  ven_window = window_create();
  WindowHandlers handlers = {
     .load = window_load,
     .unload = window_unload,
  };
  window_set_window_handlers(ven_window, (WindowHandlers) handlers);
  window_push++;
  window_stack_push(ven_window, true);
}