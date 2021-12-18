typedef struct strlock {
	int state
} lock_t;

void lock(lock_t *);
void release(lock_t *);
void lock_init(lock_t *, int);
int lock_state(lock_t * lk);
