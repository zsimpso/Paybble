#include <pebble.h>
#include "header.h"  

Window * cpay_window;

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
      finish_init();
      
      DictionaryIterator *iter;
      app_message_outbox_begin(&iter);
      char * phone_num = (char*)malloc(11 * sizeof(char));
      phone_num[0] = cont_num[0];
      phone_num[1] = cont_num[1];
      phone_num[2] = cont_num[2];
      phone_num[3] = cont_num[4];
      phone_num[4] = cont_num[5];
      phone_num[5] = cont_num[6];
      phone_num[6] = cont_num[8];
      phone_num[7] = cont_num[9];
      phone_num[8] = cont_num[10];
      phone_num[9] = cont_num[11];
      phone_num[10] = '\0';
      Tuplet value = TupletCString(1, phone_num);
      dict_write_tuplet(iter, &value);
      int number = (int)(amount * 10);
      dict_write_int(iter, 2, &number, sizeof(int), 0);
      app_message_outbox_send();
      
      break;
    case 1:
      amount = 0;
      was_back = 1;
      show_home();
      break;
  }
}

static void window_load(Window *window)
{ 
  char * buff = (char*)malloc(100 * sizeof(char*));
  if(amount > 1) snprintf(buff, 100, "Are you sure you want to send $%2d.00 to %s?", (int)amount, cont_name);
  else snprintf(buff, 100, "Are you sure you want to send $0.10 to %s?", cont_name);
  tlayer = text_layer_create(GRect(0, 0, 144, 55 + 12));
  text_layer_set_text(tlayer, buff);
  text_layer_set_background_color(tlayer, GColorClear);
  text_layer_set_text_color(tlayer, GColorBlack);
  text_layer_set_text_alignment(tlayer, GTextAlignmentCenter);
  text_layer_set_font(tlayer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(tlayer));
  
  menu_layer = menu_layer_create(GRect(0, 55 + 12, 144, 152 - 55 - 12));
  menu_layer_set_click_config_onto_window(menu_layer, cpay_window);
  MenuLayerCallbacks callbacks = {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(cpay_window), menu_layer_get_layer(menu_layer));
  free(buff);
}
 
void cpay_deinit()
{
  window_push--;
  window_destroy(cpay_window);
  menu_layer_destroy(menu_layer);
}

static void window_unload(Window *window)
{
  text_layer_destroy(tlayer);
  cpay_deinit();
}
 
void cpay_init()
{
  cpay_window = window_create();
  WindowHandlers handlers = {
     .load = window_load,
     .unload = window_unload,
  };
  window_set_window_handlers(cpay_window, (WindowHandlers) handlers);
  window_push++;
  window_stack_push(cpay_window, true);
}