#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "caq.h"

/*#define n (4)*/

/*
int Q[n];
int head = 0;
int tail = 0;
*/

__attribute__ ((nonnull (1, 2), nothrow))
void init_queue (
   caq_t *restrict q,
   void *restrict arr,
   size_t esz, size_t n) {
	q->Q = arr;
	q->esz = esz;
	q->n = n;
	q->head = 0;
	q->tail = 0;
}

int alloc_queue (caq_t *q, size_t esz, size_t n) {
	void *arr = malloc (n * esz);
	if (arr == NULL) return -1;
	init_queue (q, arr, esz, n);
	return 0;
}

void free_queue (caq_t *q) {
	free (q->Q);
}

void *enqueue (caq_t *q) {
	/*puts ("enqueue ()");*/
   void *ret;
   if (isfull (q)) /*return -1;*/
      return NULL;
   /*memcpy (q->Q + q->esz * q->tail, x, q->esz);*/
   ret = (void *) ((char *) q->Q + q->esz * q->tail);
   q->tail = (q->tail + 1) % q->n;
   /*return 0;*/
   return ret;
}

void *dequeue (caq_t *q) {
   void *x;
   if (isempty (q)) return NULL;
   x = (void *) ((char *) q->Q + q->esz * q->head);
   q->head = (q->head + 1) % q->n;
   return x;
}

__attribute__ ((pure))
bool isempty (caq_t *q) {
   return q->head == q->tail;
}

__attribute__ ((pure))
bool isfull (caq_t *q) {
   return q->head == (q->tail + 1) % q->n;
}

__attribute__ ((pure))
void *gethead(caq_t *q) {
   if (isempty (q)) return NULL;
   return (void *) ((char *) q->Q + q->esz * q->head);
}


void dumpq(caq_t *q, int i) {
   void *head = gethead (q);
   printf("i:%i, head:%i,", i, (int) q->head);
   if (head == NULL)
      printf(" tail:%i, Q[head]:NULL\n",
      (int) q->tail);
   else
      printf(" tail:%i, Q[head]:%i\n",
         (int) q->tail, *(int *) head);
}