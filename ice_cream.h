#ifndef DEFINES_H
#define DEFINES_H

#define STORE_SIZE 50
#define ITEM_NAME_LENGTH 50
#define DEPARTMENT_NAME_LENGTH 20
#define EXPIRATION_DATE_STRING_LENGTH 11
#define MAX_ITEMS 40
#define MAX_DESCRIPTION 100
#define ITEM_FIELDS 4
#define success 0
#define fail 1
#define delimiter_size 3
#define TRUE 1
#define FALSE 0
#define go_on 23
#define PRINT_STORE 1
#define	SORT_BY_EX_DATE 2
#define	SORT_BY_PRICE 3	
#define UPDATE_INVENTORY 4
#define HALT 0
#define ilegal_input 69
#define bye 420

typedef struct _item item;

void reception();
void fill_date(char year_arr[4], char month_arr[2], char day_arr[2], char date[11]);
int fill_struct(item* product);
int operation_scan();
void print_items(int actual_size, item* product);
int compare_price(const void* a, const void* b);
void sort_store_by_price(int actual_size, item* product);
int compare_date(const void* a, const void* b);
void sort_store_by_date(int actual_size, item* product);
int is_expired(item product, int curr_day, int curr_month, int curr_year);
int update_store(int actual_size, item* product);
int navigate(int opt, int actual_size, item* product);








#endif // !DEFINES_H
