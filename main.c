#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "McGoogles.h"

// Feel free to play with these numbers! This is a great way to
// test your implementation.
#define MCGOOGLES_SIZE 100
#define NUM_CUSTOMERS 10
#define NUM_COOKS 5
#define ORDERS_PER_CUSTOMER 10
#define EXPECTED_NUM_ORDERS NUM_CUSTOMERS * ORDERS_PER_CUSTOMER

// Global variable for the restaurant.
McGoogles *mcg;

/**
 * Thread funtion that represents a customer. A customer should:
 *  - allocate space (memory) for an order.
 *  - select a menu item.
 *  - populate the order with their menu item and their customer ID.
 *  - add their order to the restaurant.
 */
void* McGooglesCustomer(void* tid) {
    // int customer_id = (int)(long) tid;
    int customer_id = *(int *) tid;
    
    for (int i = 0; i < ORDERS_PER_CUSTOMER; i++) {
        Order* order = malloc(sizeof(Order));
        order->menu_item = PickRandomMenuItem();
        order->customer_id = customer_id;
        order->next = NULL;
          
        AddOrder(mcg, order);
        printf("Added order number %d\n", mcg->current_size);
    }
	return NULL;
}

/**
 * Thread function that represents a cook in the restaurant. A cook should:
 *  - get an order from the restaurant.
 *  - if the order is valid, it should fulfill the order, and then
 *    free the space taken by the order.
 * The cook should take orders from the restaurants until it does not
 * receive an order.
 */
void* McGooglesCook(void* tid) {
    int cook_id = *(int *) tid;
	int orders_fulfilled = 0;
    while (!IsEmpty(mcg)) {
        Order* order = GetOrder(mcg);
        // valid order
        if (order) {
            // free the space taken by order
            free(order);
        }
    }
	printf("Cook #%d fulfilled %d orders\n", cook_id, orders_fulfilled);
	return NULL;
}

/**
 * Runs when the program begins executing. This program should:
 *  - open the restaurant
 *  - create customers and cooks
 *  - wait for all customers and cooks to be done
 *  - close the restaurant.
 */
int main() {
    pthread_t customers[NUM_CUSTOMERS];
    pthread_t cooks[NUM_COOKS];
    
    mcg = OpenRestaurant(NUM_COOKS, EXPECTED_NUM_ORDERS);

    // Create customers and cooks threads
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_create(&customers[i], NULL, McGooglesCustomer(&i), NULL);
    }
    for (int i = 0; i < NUM_COOKS; i++) {
        printf("Entered cook threads\n");
        pthread_create(&cooks[i], NULL, McGooglesCook(&i), NULL);
    }
        
    // Wait for all customers and cooks threads
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }
    for (int i = 0; i <NUM_COOKS; i++) {
        pthread_join(cooks[i], NULL);
    }
    
    CloseRestaurant(mcg);
    return 0;
}