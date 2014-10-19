#include <pebble.h>
#include "header.h"  

Window * camt_window;

static MenuLayer * menu_layer;

static TextLayer * tlayer;
 
static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "Yes", NULL, NULL);
      break;
    case 1:
      menu_cell_basic_draw(ctx, cell_layer, "No", NULL, NULL);
      break;
  }
}
 
static uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
  return 2;
}
 
static void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    case 0:
      cpay_init();
      break;
    case 1:
      amount = 0;
      int i = 0;
      for(i = 0; i < (2 + was_cust); i++){
        window_stack_pop(true);
      }
      was_back = 1;
      amt_init();
      break;
  }
}

static void window_load(Window *window)
{ 
  char * buff = (char*)malloc(40 * sizeof(char*));
  if(amount > 1) snprintf(buff, 40, "Is this amount correct?  $%2d.00", (int)amount);
  else snprintf(buff, 40, "Is this amount correct?  $0.10");
  tlayer = text_layer_create(GRect(0, 0, 144, 30 + 12));
  text_layer_set_text(tlayer, buff);
  text_layer_set_background_color(tlayer, GColorClear);
  text_layer_set_text_color(tlayer, GColorBlack);
  text_layer_set_text_alignment(tlayer, GTextAlignmentCenter);
  text_layer_set_font(tlayer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(tlayer));
  
  menu_layer = menu_layer_create(GRect(0, 30 + 12, 144, 152 - 30 - 12));
  menu_layer_set_click_config_onto_window(menu_layer, camt_window);
  MenuLayerCallbacks callbacks = {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(camt_window), menu_layer_get_layer(menu_layer));
  free(buff);
}
 
void camt_deinit()
{
  window_push--;
  window_destroy(camt_window);
  menu_layer_destroy(menu_layer);
}

static void window_unload(Window *window)
{
  text_layer_destroy(tlayer);
  camt_deinit();
}
 
void camt_init()
{
  camt_window = window_create();
  WindowHandlers handlers = {
     .load = window_load,
     .unload = window_unload,
  };
  window_set_window_handlers(camt_window, (WindowHandlers) handlers);
  window_push++;
  window_stack_push(camt_window, true);
}