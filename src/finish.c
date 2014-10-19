#include <pebble.h>
#include "header.h"  

Window * finish_window;

static MenuLayer * menu_layer;

static TextLayer * tlayer;
 
static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "OK", NULL, NULL);
      break;
  }
}
 
static uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
  return 1;
}

static void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    case 0:
      show_home();
      break;
  }
}

static void window_load(Window *window)
{ 
  char * buff = (char*)malloc(100 * sizeof(char*));
  if(amount > 1) snprintf(buff, 100, "Successfully sent $%2d.00 to %s.", (int)amount, cont_name);
  else snprintf(buff, 100, "Successfully sent $0.10 to %s.", cont_name);
  tlayer = text_layer_create(GRect(0, 0, 144, 45 + 12));
  text_layer_set_text(tlayer, buff);
  text_layer_set_background_color(tlayer, GColorClear);
  text_layer_set_text_color(tlayer, GColorBlack);
  text_layer_set_text_alignment(tlayer, GTextAlignmentCenter);
  text_layer_set_font(tlayer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(tlayer));
  
  menu_layer = menu_layer_create(GRect(0, 45 + 12, 144, 152 - 45 - 12));
  menu_layer_set_click_config_onto_window(menu_layer, finish_window);
  MenuLayerCallbacks callbacks = {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(finish_window), menu_layer_get_layer(menu_layer));
  free(buff);
}
 
void finish_deinit()
{
  window_push--;
  window_destroy(finish_window);
  menu_layer_destroy(menu_layer);
}

static void window_unload(Window *window)
{
  text_layer_destroy(tlayer);
  finish_deinit();
}
 
void finish_init()
{
  finish_window = window_create();
  WindowHandlers handlers = {
     .load = window_load,
     .unload = window_unload,
  };
  window_set_window_handlers(finish_window, (WindowHandlers) handlers);
  window_push++;
  window_stack_push(finish_window, true);
}