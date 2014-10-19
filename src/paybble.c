#include <pebble.h>
#include "header.h"
  
char * cont_name;
char * cont_num;
double amount;
int window_push;
int was_cust;
int was_back;
  
Window * home_window;

static TextLayer * tlayer;

static MenuLayer * menu_layer;
 
static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "Contacts", NULL, NULL);
      break;
//    case 1:
//      menu_cell_basic_draw(ctx, cell_layer, "Paypal", NULL, NULL);
//      break;
  }
}
 
static uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
  return 1;
}
 
static void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    case 0: //venmo contacts
      ven_init();
      break;
//    case 1: //paypal contacts
//      pay_init();
//      break;
  }
}

static void window_load(Window *window)
{
  tlayer = text_layer_create(GRect(0, 0, 144, 30 + 12));
  text_layer_set_text(tlayer, "Paybble");
  text_layer_set_background_color(tlayer, GColorClear);
  text_layer_set_text_color(tlayer, GColorBlack);
  text_layer_set_text_alignment(tlayer, GTextAlignmentCenter);
  text_layer_set_font(tlayer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(tlayer));
  
  menu_layer = menu_layer_create(GRect(0, 36 + 12, 144, 168 - 30 - 12));
  menu_layer_set_click_config_onto_window(menu_layer, home_window);
  MenuLayerCallbacks callbacks = {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(home_window), menu_layer_get_layer(menu_layer));
}
 
static void window_unload(Window *window)
{
 text_layer_destroy(tlayer);
}

void home_deinit()
{
  window_push--;
  window_destroy(home_window);
  menu_layer_destroy(menu_layer);
}
 
void home_init()
{
  
  message_init();
 // APP_LOG(APP_LOG_LEVEL_DEBUG, "After message init");
  cont_name = NULL;
  cont_num = NULL;
  amount = 0;
  was_cust = 0;
  window_push = 0;
  was_back = 0;
  home_window = window_create();
  WindowHandlers handlers = {
     .load = window_load,
     .unload = window_unload,
  };
  window_set_window_handlers(home_window, (WindowHandlers) handlers);
  window_push++;
  window_stack_push(home_window, !was_back);
}

void show_home(){
  window_stack_pop_all(true);
  home_init();
}
 
int main(void)
{
  home_init();
 // APP_LOG(APP_LOG_LEVEL_DEBUG, "After home init");
  app_event_loop();
  home_deinit();
}