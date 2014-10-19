#include <pebble.h>
  

Window * pay_window;

TextLayer * tlayer;

MenuLayer * menu_layer;
 
static void draw_row_callback(GContext *ctx, Layer *cell_layer, MenuIndex *cell_index, void *callback_context)
{
  switch(cell_index->row){
    case 0:
      menu_cell_basic_draw(ctx, cell_layer, "Contact 1", "111-111-1111", NULL);
    //  cont_name = "Contact1";
     // cont_num = "111-111-1111";
      break;
    case 1:
      menu_cell_basic_draw(ctx, cell_layer, "Contact2", "222-222-2222", NULL);
     // cont_name = "Contact2";
     // cont_num = "222-222-2222";
      break;
    case 2:
      menu_cell_basic_draw(ctx, cell_layer, "Contact3", "333-333-3333", NULL);
     // cont_name = "Contact3";
     // cont_num = "333-333-3333";
      break;
  }
}
 
static uint16_t num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *callback_context)
{
  return 3;
}
 
static void select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context)
{
  
  
}

static void window_load(Window *window)
{ 
  menu_layer = menu_layer_create(GRect(0, 12, 144, 168 - 12));
  menu_layer_set_click_config_onto_window(menu_layer, pay_window);
  MenuLayerCallbacks callbacks = {
    .draw_row = (MenuLayerDrawRowCallback) draw_row_callback,
    .get_num_rows = (MenuLayerGetNumberOfRowsInSectionsCallback) num_rows_callback,
    .select_click = (MenuLayerSelectCallback) select_click_callback,
  };
  menu_layer_set_callbacks(menu_layer, NULL, callbacks);
  layer_add_child(window_get_root_layer(pay_window), menu_layer_get_layer(menu_layer));
}

extern void pay_deinit()
{
  window_destroy(pay_window);
  menu_layer_destroy(menu_layer);
}
 
static void window_unload(Window *window)
{
 pay_deinit();
}
 
extern void pay_init()
{
  pay_window = window_create();
  WindowHandlers handlers = {
     .load = window_load,
     .unload = window_unload,
  };
  window_set_window_handlers(pay_window, (WindowHandlers) handlers);
  window_stack_push(pay_window, true);
}