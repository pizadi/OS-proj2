#include "mkshlock.h"
#include<linux/module.h>

#define DEVICE_NAME "bank"
void lock(lock_t * lk) {
	while (lk->state);
	lk->state = 1;
}

void release(lock_t * lk) {
	lk->state = 0;
}

void lock_init(lock_t * lk, int s){
	lk->state = s;
}

int lock_state(lock_t * lk){
	return lk->state;
}

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");
