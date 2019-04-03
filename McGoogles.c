#include "McGoogles.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

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
    int rand_index = ((rand() % (McGooglesMenuLength - 1 + 1)) + 1) - 1;
    return McGooglesMenu[rand_index];
}

McGoogles* OpenRestaurant(int max_size, int expected_num_orders) {
    McGoogles* mcgo = malloc(sizeof(McGoogles));
    mcgo->current_size = 0;
    mcgo->max_size = max_size;
    mcgo->next_order_number = 1;
    mcgo->orders_handled = 0;
    mcgo->expected_num_orders = expected_num_orders;
    pthread_mutex_init(&(mcgo->mutex), NULL);
    pthread_cond_init(&(mcgo->can_add_orders), NULL);
    pthread_cond_init(&(mcgo->can_get_orders), NULL);
    mcgo->orders = NULL;
    printf("Restaurant is open!\n");
    return mcgo;
}

void CloseRestaurant(McGoogles* mcg) {
    pthread_mutex_destroy(&(mcg->mutex));
    pthread_cond_destroy(&(mcg->can_add_orders));
    pthread_cond_destroy(&(mcg->can_get_orders));
    free(mcg->orders);
    free(mcg);
    printf("Restaurant is closed!\n");
}

int AddOrder(McGoogles* mcg, Order* order) {
    pthread_mutex_lock(&(mcg->mutex));
    while (mcg->current_size >= mcg->max_size) {
        pthread_cond_wait(&(mcg->can_add_orders), &(mcg->mutex));
    }
    pthread_cond_signal(&(mcg->can_get_orders));
    
    order->order_number = mcg->next_order_number;
    AddOrderToBack(&(mcg->orders), order); 
    mcg->current_size = mcg->current_size + 1;
    mcg->next_order_number = mcg->next_order_number + 1;
    pthread_mutex_unlock(&(mcg->mutex));
    return order->order_number;
}

Order *GetOrder(McGoogles* mcg) {
    pthread_mutex_lock(&(mcg->mutex));
    while (IsEmpty(mcg)) {
        pthread_cond_wait(&(mcg->can_get_orders), &(mcg->mutex));
    }
    Order* order = mcg->orders;
    if (!order) {
        printf("Order is null\n");
        printf("Current size is %d\n", mcg->current_size);
    }
    printf("Got order %d\n", order->order_number);
    mcg->orders = mcg->orders->next;
    order->next = NULL;
    

    mcg->orders_handled = mcg->orders_handled + 1;
    mcg->current_size = mcg->current_size - 1;
    // signal customer to make order
    pthread_cond_signal(&(mcg->can_add_orders));
    pthread_mutex_unlock(&(mcg->mutex));
    return order;
}

// Optional helper functions (you can implement if you think they would be useful)
bool IsEmpty(McGoogles* mcg) {
    if (!mcg->current_size)
        return true;
    return false;
}

bool IsFull(McGoogles* mcg) {
    if (mcg->max_size >= mcg->current_size)
        return true;
    return false;
}

// TODO: problem with linked list
void AddOrderToBack(Order **orders, Order *order) {
    // if it's first order
    if (*orders == NULL) {
        *orders = order;
    }
    else {
        Order* tmp = *orders;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = order;
    }
}
