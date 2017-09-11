#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <caq.h>

/*#define n (4)*/

/*
int Q[n];
int head = 0;
int tail = 0;
*/

__attribute__ ((leaf, nonnull (1, 2), nothrow))
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

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
int alloc_queue (
   caq_t *restrict q,
   size_t esz, size_t n) {
   void *arr = malloc (n * esz);
   error_check (arr == NULL) return -1;
   init_queue (q, arr, esz, n);
   return 0;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_queue (caq_t *restrict q) {
      free (q->Q);
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
void *enqueue (caq_t *restrict q) {
	/*puts ("enqueue ()");*/
   void *ret;
   error_check (isfull (q) != false) /*return -1;*/
      return NULL;
   /*memcpy (q->Q + q->esz * q->tail, x, q->esz);*/
   ret = (void *) ((char *) q->Q + q->esz * q->tail);
   q->tail = (q->tail + 1) % q->n;
   /*return 0;*/
   return ret;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
void *dequeue (caq_t *restrict q) {
   void *x;
   error_check (isempty (q) != false) return NULL;
   x = (void *) ((char *) q->Q + q->esz * q->head);
   q->head = (q->head + 1) % q->n;
   return x;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isempty (caq_t const *restrict q) {
   return q->head == q->tail;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isfull (caq_t const *restrict q) {
   return q->head == (q->tail + 1) % q->n;
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void *gethead(caq_t const *restrict q) {
   error_check (isempty (q) != false) return NULL;
   return (void *) ((char *) q->Q + q->esz * q->head);
}

__attribute__ ((nonnull (1), nothrow))
void dumpq(caq_t const *restrict q, int i) {
   void *head = gethead (q);
   printf("i:%i, head:%i,", i, (int) q->head);
   if (head == NULL)
      printf(" tail:%i, Q[head]:NULL\n",
      (int) q->tail);
   else
      printf(" tail:%i, Q[head]:%i\n",
         (int) q->tail, *(int *) head);
}