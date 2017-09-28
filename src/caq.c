#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <caq.h>

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_queue (
   caq_t *restrict q,
   void *restrict data,
   size_t esz, size_t n) {
   init_array (&(q->array), data, esz, n);
   q->head = 0;
   q->tail = 0;
}

__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result))
int alloc_queue (
   caq_t *restrict q,
   size_t esz, size_t n) {
   error_check (alloc_array (&(q->array), esz, n) != 0) return -1;
   q->head = 0;
   q->tail = 0;
   return 0;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_queue (caq_t *restrict q) {
   free_array (&(q->array));
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
void *enqueue (caq_t *restrict q) {
	/*puts ("enqueue ()");*/
   void *restrict ret;
   TODO (why do error checking ?)
   error_check (isfull (q) != false) /*return -1;*/
      return NULL;
   /*memcpy (q->Q + q->esz * q->tail, x, q->esz);*/
   ret = index_array (&(q->array), q->tail);
   q->tail = (q->tail + 1) % q->array.n;
   /*return 0;*/
   return ret;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
void *dequeue (caq_t *restrict q) {
   void *restrict x;
   error_check (isempty (q) != false) return NULL;
   x = index_array (&(q->array), q->head);
   q->head = (q->head + 1) % q->array.n;
   return x;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isempty (caq_t const *restrict q) {
   return q->head == q->tail;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isfull (caq_t const *restrict q) {
   return q->head == (q->tail + 1) % q->array.n;
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void *gethead(caq_t const *restrict q) {
   error_check (isempty (q) != false) return NULL;
   return index_array (&(q->array), q->head);
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