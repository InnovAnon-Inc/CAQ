#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "caq.h"

/*#define n (4)*/

/*
int Q[n];
int head = 0;
int tail = 0;
*/

void init_queue (caq_t *q, void *arr, size_t esz, size_t n) {
	q->Q = arr;
	q->esz = esz;
	q->n = n;
	q->head = 0;
	q->tail = 0;
}

int alloc_queue (caq_t *q, size_t esz, size_t n) {
	int *arr = malloc (n * esz);
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
   ret = q->Q + q->esz * q->tail;
   q->tail = (q->tail + 1) % q->n;
   /*return 0;*/
   return ret;
}

void *dequeue (caq_t *q) {
   void *x;
   if (isempty (q)) return NULL;
   x = q->Q + q->esz * q->head;
   q->head = (q->head + 1) % q->n;
   return x;
}

bool isempty (caq_t *q) {
   return q->head == q->tail;
}

bool isfull (caq_t *q) {
   return q->head == (q->tail + 1) % q->n;
}

void *gethead(caq_t *q) {
   if (isempty (q)) return NULL;
   return q->Q + q->esz * q->head;
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