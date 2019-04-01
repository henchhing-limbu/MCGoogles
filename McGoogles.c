#include "McGoogles.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

bool IsEmpty(McGoogles* mcg);
bool IsFull(McGoogles* mcg);
void AddOrderToBack(Order **orders, Order *order);

MenuItem McGooglesMenu[] = { 
    "GoogMac", 
    "GoogDouble", 
    "GoogChicken", 
    "GoogQuarterPounder", 
    "GoogNuggets",
    "GoogCrispyChicken",
    "GoogHamburger",
    "GoogCheeseBurger",
    "GoogSmokeHouseBurger",
    "GoogFiletOFish",
};
int McGooglesMenuLength = 10;

MenuItem PickRandomMenuItem() {
    return NULL;
}

// TODO:
static void init_order(Order* order) {
    order->menu_item = "";
    order->customer_id = -1;
    order->order_number = -1;
    order->next = NULL;
}

McGoogles* OpenRestaurant(int max_size, int expected_num_orders) {
    McGoogles* mcgo;
    mcgo->current_size = 0;
    mcgo->max_size = max_size;
    mcgo->next_order_number = 0;
    mcgo->orders_handled = 0;
    mcgo->expected_num_orders = expected_num_orders;
    pthread_mutex_init(&mcgo->mutex, NULL);
    pthread_cond_init(&(mcgo->can_add_orders), NULL);
    pthread_cond_init(&(mcgo->can_get_orders), NULL);
    
    Order orders[expected_num_orders];
    /*
    for (int i = 0; i < expected_num_orders; i++) {
        init_order(&orders[i]);
    }*/
    printf("Restaurant is open!\n");
    return mcgo;
}

void CloseRestaurant(McGoogles* mcg) {
    printf("Restaurant is closed!\n");
}

int AddOrder(McGoogles* mcg, Order* order) {
    return -1;
}

Order *GetOrder(McGoogles* mcg) {
    return NULL;
}

// Optional helper functions (you can implement if you think they would be useful)
// TODO: don't know if this implementation is right
bool IsEmpty(McGoogles* mcg) {
    if (mcg->orders_handled == mcg->expected_num_orders)
        return true;
    return false;
}

bool IsFull(McGoogles* mcg) {
    if (mcg->max_size >= current_size)
        return true;
    return false;
}

void AddOrderToBack(Order **orders, Order *order) {
    
}
