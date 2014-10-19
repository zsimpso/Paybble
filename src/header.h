#pragma once
  
#define NUM_CONTACTS 3

extern char * cont_name;
extern char * cont_num;
extern double amount;
extern int window_push;
extern int was_cust;
extern int was_back;

void home_init();  //start page
void ven_init(); //venmo contacts
void amt_init(); //pick amount
void camt_init(); //confirm amount
void cpay_init(); //confirm payment
//void custamt_init(); //custom payment
void finish_init(); //finish screen

void show_home();

void message_init();

enum{
  KEY_NUM = 1,
  KEY_NAME = 2
};