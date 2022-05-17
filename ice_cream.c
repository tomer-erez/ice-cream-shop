#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Ex4_q1_207015579.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
date; roughly middle of may 2022
name; tomer erez
id; 207015579
code; this code will manage an ice-cream shop's items
*/




typedef struct _item {						
	char item_name[ITEM_NAME_LENGTH];
	char department[DEPARTMENT_NAME_LENGTH];
	char expiration_date[EXPIRATION_DATE_STRING_LENGTH];
	double price;
	int available;
	int year;								//added for compare functions
	int month;								//added for compare functions
	int day;								//added for compare functions
}item;          

void reception() {								
	printf("### Welcome To Sience For Ice Creame Shop ###\n");
	printf("Please Enter up to 40 products.\n");
	printf("The items should be intered int the format below:\n");
	printf("item_name_*_department_*_expiration_*_price_*_available.\n");
	printf("The expiration_date should be in the formet: dd.mm.yyyy\n");
	printf("The price in shekels should be in the formet: xx.yy\n\n");
	printf("In order to enter less than 40 items just enter the string STOP\n\n");
}

 
void fill_date(char year_arr[4], char month_arr[2], char day_arr[2], char date[11]) {//fill arrays from original date format
	day_arr[0] = date[0];
	day_arr[1] = date[1];
	month_arr[0] = date[3];
	month_arr[1] = date[4];
	year_arr[0] = date[6];
	year_arr[1] = date[7];
	year_arr[2] = date[8];
	year_arr[3] = date[9];
}


int fill_struct(item* product) {//fill struct, input=ptr to array of items, output-num of items inserted to the shop
	int i = 0, stop = fail;
	char tmp[delimiter_size];
	while (i < MAX_ITEMS && stop == fail) {


		int retval1 = scanf("%[^_||\n]s", &(product->item_name)); if (retval1 == 0)break;//scan a string until _ sign ,or in case of stop until newline
		if (strstr(product->item_name, "STOP") != NULL || strstr(product->item_name, "stop")) break;
		int ret1 = scanf("%3c", tmp);


		int retval2 = scanf("%[^_]s", &(product->department)); if (retval2 == 0)break;//scan a string until _ sign
		int ret2 = scanf("%3c", tmp);


		int retval3 = scanf("%[^_]s", &(product->expiration_date)); if (retval3 == 0)break;//scan a string until _ sign	
		(product->expiration_date)[EXPIRATION_DATE_STRING_LENGTH - 1] = '\0';//make null terminated
		char year_arr[4], month_arr[2], day_arr[2];
		fill_date(year_arr, month_arr, day_arr, product->expiration_date);//grant each struct in the array with numerical date values for comparison purposes
		product->year = atoi(year_arr); product->month = atoi(month_arr); product->day = atoi(day_arr);//fill the structs from the temp arrays
		int ret3 = scanf("%3c", tmp);


		int retval4 = scanf("%lf", &(product->price)); if (retval4 == 0)break;
		int ret4 = scanf("%3c", tmp);


		int retval5 = scanf("%d", &(product->available)); if (retval5 == 0)break;
		char enter = getchar();


		product++;
		i++;
	}
	int actual_size = i;
	return actual_size;//return how many items were inserted to the shop	
}

int operation_scan() {
	printf("\n\nPlease chose the operation for the automated system to do.\n");
	printf("Choose 1 in order to print the products in the store.\n");
	printf("Choose 2 in order to sort the inventory by the expiration date.\n");
	printf("Choose 3 in order to sort the inventory by the price.\n");
	printf("Choose 4 in order to update the inventory by after throwing the expired items.\n");
	printf("Choose 0 at any time in order to stop the program and display the final inventory.\n\n");		//print menu

	int option;
	int ret = scanf("%d", &option);																		//scan user choice
	if (ret == HALT) return HALT;
	
	if (option != HALT && option != PRINT_STORE && option != SORT_BY_EX_DATE && option != SORT_BY_PRICE && option != UPDATE_INVENTORY) return ilegal_input;
	if (option == HALT) printf("Thank you for visiting our store.\nHave a wonderful day.\n");
	return option;
}

void print_items(int actual_size, item* product) {
	for (int j = 0; j < actual_size; j++) {//print array
		printf("\nItem number %d\n", j + 1);
		printf("item name = %s\n", product->item_name);
		printf("department = %s\n", product->department);
		printf("expiration date = %s\n", product->expiration_date);
		printf("price = %lf\n", product->price);
		printf("units left = %d\n", product->available);
		product++;
	}
}

int compare_price(const void* a, const void* b)
{
	item* proA = (item*)a;
	item* proB = (item*)b;

	return (proA->price - proB->price);
}

void sort_store_by_price(int actual_size, item* product) {
	printf("You chose to sort the inventory by the price.\n");
	qsort(product, actual_size, sizeof(item), compare_price);
}

int compare_date(const void* a, const void* b) {
	item* proA = (item*)a;
	item* proB = (item*)b;

	if (proA->year != proB->year) return (proA->year - proB->year);
	else if (proA->month != proB->month) return(proA->month - proB->month);
	else return (proA->day - proB->day);
}

void sort_store_by_date(int actual_size, item* product) {
	printf("You chose to sort the inventory by the expiration date.\n");
	qsort(product, actual_size, sizeof(item), compare_date);
}

int is_expired(item product, int curr_day, int curr_month, int curr_year) {
	if ((product.year < curr_year) || ((product.year == curr_year) && (product.month < curr_month)) || ((product.year == curr_year) && (product.month == curr_month) && (product.day <= curr_day)))//seems right
		return TRUE;
	return FALSE;



}

int update_store(int actual_size, item* product) {
	printf("enter the current date in the format: dd.mm.yyyy\n");
	int k = 0;
	char d[EXPIRATION_DATE_STRING_LENGTH];
	d[EXPIRATION_DATE_STRING_LENGTH - 1] = '\0';

	int retval3 = scanf("%10s", &d); if (retval3 == 0) { printf("invalid date format"); return fail; }// lines to init array and scan date

	char year_arr[4], month_arr[2], day_arr[2];
	fill_date(year_arr, month_arr, day_arr, d); //fill

	int curr_year = atoi(year_arr);
	int curr_month = atoi(month_arr);
	int curr_day = atoi(day_arr); //now we have date in comparative format
	int j = 0, deleted = 0;

	while (j < actual_size - 1) {
		deleted = 0;
		if (is_expired(product[j], curr_day, curr_month, curr_year) == TRUE)
		{
			for (k = j; k < actual_size - 1; k++) {//we will move every item one spot back resulting in the deletion of the expired item
				product[k] = product[k + 1];
			}
			actual_size--;
			deleted = 1;
		}
		if (deleted == 0) j++;
	}

	if (is_expired(product[actual_size - 1], curr_day, curr_month, curr_year) == TRUE) actual_size--;
	return actual_size;
}

int navigate(int opt, int actual_size, item* product) {																//scan for operation choice.
	if (opt == ilegal_input) { printf("\nillegal operation choice\n"); return bye; }  //activate desired operation., if ilegal break
	int size;
	switch (opt)
	{
	case PRINT_STORE:
		printf("You chose to print the products in the store option.\n");
		print_items(actual_size, product);
		return actual_size;
		break;

	case SORT_BY_EX_DATE:
		sort_store_by_date(actual_size, product);
		print_items(actual_size, product);
		return actual_size;
		break;

	case SORT_BY_PRICE:
		sort_store_by_price(actual_size, product);
		print_items(actual_size, product);
		return actual_size;
		break;

	case UPDATE_INVENTORY:
		printf("You chose to get rid of all expires items in the inventory.\nPlease enter the present date.\n");
		size = update_store(actual_size, product);
		actual_size = size;
		print_items(actual_size, product);
		printf("You have successfully removed all of the expired items from the inventory.\n");
		return actual_size;
		break;

	case HALT:
		return actual_size;
		break;

	default:
		return actual_size;
		break;
	}
}

int main() {
	reception();															//welcome massage
	item items[MAX_ITEMS];													//items array, consider usuing malloc
	item* ptr; ptr = items;													//ptr to array items,will be sent to the function that fills the array

	int actual_size = fill_struct(ptr);										//fill struct
	int size = actual_size;

	//fix by having ptr to actual size and update it through the code

	int flag = go_on;
	flag = operation_scan();
	while (flag != HALT) {		//while true
		size = navigate(flag, actual_size, ptr);		//do the desired opt
		actual_size = size;				// update menu- shouldve usen pointer
		flag = operation_scan();		//ask for opt from menu
	}
	return success;
}



//forks_*_silverware_*_29.07.3250_*_99.99_*_120
//yotbeta Popsicles_*_strauss_*_12.08.2022_*_16.90_*_15
//Liklakim_*_strauss_*_14.08.2022_*_23.50_*_21
//danone yogurt_*_dairy_*_01.05.2022_*_07.55_*_10
//tuti fruti_*_ice cream_*_02.01.2020_*_04.00_*_7
//cheetos_*_snack_*_02.01.2024_*_14.20_*_9
//vitaminchik_*_juice_*_02.01.2010_*_04.00_*_7








/*for (int j = 0; j < actual_size; j++) {//print array
		printf("%s\n", items[j].item_name);
		printf("%s\n", items[j].department);
		printf("%s\n", (items[j].expiration_date));
		printf("%lf\n", items[j].price);
		printf("%d\n", items[j].available);
	}*/