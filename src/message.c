#include <pebble.h>
#include "header.h"

Window *window;	
	
typedef struct Contact{
  char * name; // = 0
  char * number; // = 1
} contact;

// Key values for AppMessage Dictionary
enum {
	STATUS_KEY = 0,	
	MESSAGE_KEY = 1
};

// Write message to buffer & send
void send_message(void){
	DictionaryIterator *iter;
	
	app_message_outbox_begin(&iter);
	dict_write_uint8(iter, STATUS_KEY, 0x1);
	
	dict_write_end(iter);
  	app_message_outbox_send();
}

// Called when a message is received from PebbleKitJS
static void in_received_handler(DictionaryIterator *received, void *context) {
  
	Tuple *tuple;
	int count = 0;
  tuple = dict_read_first(received);
  
  contact ** contact_list = (contact**)malloc(NUM_CONTACTS * sizeof(contact*));
  int i;
  for(i = 0; i < NUM_CONTACTS; i++){
    contact_list[i] = (contact*)malloc(sizeof(contact));
  }
  
  while(tuple && count < NUM_CONTACTS) {
   
    if(tuple->key == KEY_NAME){ //add name
      contact_list[count]->name = (char*)malloc(tuple->length);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple: %s", (char*)tuple->value->cstring);
      strncpy(contact_list[count]->name , (char*)(tuple->value->cstring), tuple->length);
      APP_LOG(APP_LOG_LEVEL_DEBUG, "contact list: %s", contact_list[count]->name);
    }
    else if(tuple->key == KEY_NUM){ //add number
      contact_list[count]->number = (char*)malloc(tuple->length);
      strncpy(contact_list[count]->number , (char*)(tuple->value->cstring), tuple->length);
    }
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "TEST1");
   // APP_LOG(APP_LOG_LEVEL_DEBUG, "Name: %s. Number %s", contact_list[count]->name, contact_list[count]->number); //failing on this line
    // APP_LOG(APP_LOG_LEVEL_DEBUG, "TEST2");
    tuple = dict_read_next(received);
    count++;
		//APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Status: %d", (int)tuple->value->uint32); 
	}
  
}

// Called when an incoming message from PebbleKitJS is dropped
static void in_dropped_handler(AppMessageResult reason, void *context) {	
  APP_LOG(APP_LOG_LEVEL_DEBUG, "error message in dropped_in: %s", (char*)context);
}

// Called when PebbleKitJS does not acknowledge receipt of a message
static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed out send: %d", reason);
}

void message_init(void) {
	
	// Register AppMessage handlers
	app_message_register_inbox_received(in_received_handler); 
	app_message_register_inbox_dropped(in_dropped_handler); 
	app_message_register_outbox_failed(out_failed_handler);
		
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
	//send_message();
}

void message_deinit(void) {
	app_message_deregister_callbacks();
}

/*int main(void)
{
  message_init();
  app_event_loop();
  message_deinit();
}*/