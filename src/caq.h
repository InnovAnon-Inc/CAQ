#ifndef _CAQ_H_
#define _CAQ_H_

#include <stdbool.h>
#include <sys/types.h>

typedef struct {
	void *Q;
	size_t esz;
	size_t n;
	size_t head;
	size_t tail;
} caq_t;

void init_queue (caq_t *q, void *arr, size_t esz, size_t n);
int alloc_queue (caq_t *q, size_t esz, size_t n) ;
void free_queue (caq_t *q) ;

/* ret type == elem type */
void *dequeue (caq_t *q) ;
/* returns err code */
int enqueue (caq_t *q, void *e) ;
bool isempty (caq_t *q) ;
bool isfull (caq_t *q) ;
void *gethead (caq_t *q) ;
void dumpq(caq_t *q, int i) ;

#endif /* _CAQ_H_ */