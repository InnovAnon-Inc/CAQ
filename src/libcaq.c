#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mmalloc.h>

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
void free_queue (caq_t const *restrict q) {
   free_array (&(q->array));
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void enqueue (caq_t *restrict q, void const *restrict e) {
   set_array (&(q->array), q->tail, e);
   q->tail = (q->tail + 1) % q->array.n;
}

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int enqueue_chk (caq_t *restrict q, void const *restrict e) {
   error_check (isfull (q)) return -1;
   enqueue (q, e);
   return 0;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void dequeue (caq_t *restrict q, void *restrict e) {
   get_array (&(q->array), q->head, e);
   q->head = (q->head + 1) % q->array.n;
}

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int dequeue_chk (caq_t *restrict q, void *restrict e) {
   error_check (isempty (q) != false) return -1;
   dequeue (q, e);
   return 0;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isempty (caq_t const *restrict q) {
   return q->head == q->tail;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isfull (caq_t const *restrict q) {
   return q->head == (q->tail + 1) % q->array.n;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void *gethead (caq_t const *restrict q) {
   return index_array (&(q->array), q->head);
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void *gethead_chk (caq_t const *restrict q) {
   error_check (isempty (q) != false) return NULL;
   return gethead (q);
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void *gettail (caq_t const *restrict q) {
   /*error_check (isempty (q) != false) return NULL;*/
   return index_array (&(q->array), q->tail);
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void *gettail_chk (caq_t const *restrict q) {
   error_check (isempty (q) != false) return NULL;
   return gettail (q);
}

/*
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
*/

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t caqsz (size_t esz, size_t n) {
   return sizeof (caq_t) + datasz (esz, n);
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
size_t caqsz2 (caq_t const *restrict caq) {
   return caqsz (caq->array.esz, caq->array.n);
}

__attribute__ ((nothrow, warn_unused_result))
caq_t *ez_alloc_caq (size_t esz, size_t maxn) {
   void *restrict combined[2];
	size_t eszs[2];
	caq_t *restrict caq;
	void *restrict data;

	eszs[0] = sizeof (caq_t);
	eszs[1] = datasz  (esz, maxn);
	error_check (mmalloc (combined, eszs,
		eszs[0] + eszs[1], ARRSZ (eszs)) != 0)
		return NULL;
	caq  = (caq_t *restrict) combined[0];
	data = (void *restrict)  combined[1];

   init_queue (caq, data, esz, maxn);
	return caq;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void ez_free_caq (caq_t *restrict caq) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
   mfree ((void *restrict) caq);
	#pragma GCC diagnostic pop
   free (caq);
}
