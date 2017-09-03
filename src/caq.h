#ifndef _CAQ_H_
#define _CAQ_H_

#include <stdbool.h>
#include <sys/types.h>

typedef struct {
	int *Q;
	size_t n;
	size_t head;
	size_t tail;
} caq_t;

void init_queue (caq_t *q, int *arr, size_t n);
int alloc_queue (caq_t *q, size_t n) ;
void free_queue (caq_t *q) ;

/* ret type == elem type */
int dequeue (caq_t *q) ;
/* returns err code */
int enqueue (caq_t *q, int) ;
bool isempty (caq_t *q) ;
bool isfull (caq_t *q) ;
int gethead (caq_t *q) ;
void dumpq(caq_t *q, int i) ;

#endif /* _CAQ_H_ */