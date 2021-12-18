#include "mkshlock.h"

void lock(lock_t * lk) {
	while (lock_t->state);
	lock_t->state = 1;
}

void release(lock_t * lk) {
	lock_t->state = 0;
}

void lock_init(lock_t * lk, int s){
	lock_t->state = s;
}

int lock_state(lock_t * lk){
	return lock_t->state;
}
