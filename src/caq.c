#include <stdlib.h>
#include <stdio.h>

#include "caq.h"

/*#define n (4)*/

/*
int Q[n];
int head = 0;
int tail = 0;
*/

void init_queue (caq_t *q, int *arr, size_t n) {
	q->Q = arr;
	q->n = n;
	q->head = 0;
	q->tail = 0;
}

int alloc_queue (caq_t *q, size_t n) {
	int *arr = malloc (n * sizeof (int));
	if (arr == NULL) return -1;
	init_queue (q, arr, n);
	return 0;
}

void free_queue (caq_t *q) {
	free (q->Q);
}

int enqueue (caq_t *q, int x) {
   if (isfull (q)) return -1;
   q->Q[q->tail] = x;
   q->tail = (q->tail + 1) % q->n;
   return 0;
}

int dequeue (caq_t *q) {
   int x;
   if (isempty (q)) return -1;
   x = q->Q[q->head];
   q->head = (q->head + 1) % q->n;
   return x;
}

bool isempty (caq_t *q) {
   return q->head == q->tail;
}

bool isfull (caq_t *q) {
   return q->head == (q->tail + 1) % q->n;
}

int gethead(caq_t *q) {
   if (isempty (q)) return -1;
   return q->Q[q->head];
}


void dumpq(caq_t *q, int i) {
   printf("i:%i, head:%i,", i, (int) q->head);
   printf(" tail:%i, Q[head]:%i\n",
      (int) q->tail, (int) gethead (q));
}