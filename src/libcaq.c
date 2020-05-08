#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
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
   init_array (&(q->array), data, esz, n + 1);
   q->head = 0;
   q->tail = 0;
}

__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result))
int alloc_queue (
   caq_t *restrict q,
   size_t esz, size_t n) {
   error_check (alloc_array (&(q->array), esz, n + 1) != 0) return -1;
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
#ifndef NDEBUG
   size_t chk_rem  = remaining_space_caq (q);
   size_t chk_used = used_space_caq (q);
#endif
   assert (! isfull (q));
   set_array (&(q->array), q->tail, e);
   q->tail = (q->tail + 1) % q->array.n;
   assert (chk_rem  - 1 == remaining_space_caq (q));
   assert (chk_used + 1 == used_space_caq      (q));
}

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int enqueue_chk (caq_t *restrict q, void const *restrict e) {
   error_check (isfull (q) != false) return -1;
   enqueue (q, e);
   return 0;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void dequeue (caq_t *restrict q, void *restrict e) {
#ifndef NDEBUG
   size_t chk_rem  = remaining_space_caq (q);
   size_t chk_used = used_space_caq (q);
#endif
   assert (! isempty (q));
   get_array (&(q->array), q->head, e);
   q->head = (q->head + 1) % q->array.n;
   assert (chk_rem  + 1 == remaining_space_caq (q));
   assert (chk_used - 1 == used_space_caq      (q));
}

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int dequeue_chk (caq_t *restrict q, void *restrict e) {
   error_check (isempty (q) != false) return -1;
   dequeue (q, e);
   return 0;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isempty (caq_t const *restrict q) {
   if (q->head == q->tail) {
      assert (used_space_caq (q) == 0);
      assert (remaining_space_caq (q) == q->array.n - 1);
      return true;
   }
   assert (used_space_caq (q) > 0);
   assert (remaining_space_caq (q) < q->array.n - 1);
   return false;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isfull (caq_t const *restrict q) {
   if (q->head == (q->tail + 1) % q->array.n) {
      assert (used_space_caq (q) == q->array.n - 1);
      assert (remaining_space_caq (q) == 0);
      return true;
   }
   assert (used_space_caq (q) < q->array.n - 1);
   assert (remaining_space_caq (q) > 0);
   return false;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void *gethead (caq_t const *restrict q) {
   assert (! isempty (q));
   return index_array (&(q->array), q->head);
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void *gethead_chk (caq_t const *restrict q) {
   error_check (isempty (q) != false) return NULL;
   return gethead (q);
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void *gettail (caq_t const *restrict q) {
   assert (! isempty (q));
   return index_array (&(q->array), (q->tail - 1) % q->array.n);
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
   return sizeof (caq_t) + datasz (esz, n + 1);
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
size_t caqsz2 (caq_t const *restrict caq) {
   return caqsz (caq->array.esz, caq->array.n);
}

__attribute__ ((nothrow, warn_unused_result))
caq_t *ez_alloc_caq (size_t esz, size_t maxn) {
      void *restrict *restrict combined[2];
      size_t eszs[2];
      void  *restrict caq;
      void  *restrict data;
      /*caq_t *restrict caq;*/

      eszs[0] = sizeof (caq_t);
      eszs[1] = datasz (esz, maxn + 1);
      combined[0] = &caq;
      combined[1] = &data;
      /*combined[0] = (void *restrict *restrict) &caq;
        combined[1] = (void *restrict *restrict) &data;*/
      error_check (mmalloc2 (combined, eszs,
      	eszs[0] + eszs[1], ARRSZ (eszs)) != 0)
      	return NULL;

      init_queue ((caq_t *restrict) caq, data, esz, maxn);
      return (caq_t *restrict) caq;
   /*return (caq_t *restrict) *(combined[0]);*/
   /*
   void *restrict tmp;
   caq_t *restrict caq;
   void *restrict data;
   tmp = malloc (caqsz (esz, max));
   error_check (tmp == NULL) return -1;
   caq = (caq_t *restrict) tmp;
   (char *restrict) tmp + sizeof (caq_t)
   */
}

__attribute__ ((leaf, nonnull (1), nothrow))
void ez_free_caq (caq_t *restrict caq) {
   /*free_queue (caq);*/
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
   mfree2 ((void *restrict) caq);
	#pragma GCC diagnostic pop
   /*free (caq);*/
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
size_t used_space_caq (caq_t const *restrict caq) {
   size_t ret;
   if (caq->head <= caq->tail)
      ret = caq->tail - caq->head;
   else
      ret = caq->tail /*+ 1*/ + (caq->array.n - caq->head);
   assert (ret <= caq->array.n - 1);
   return ret;
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
size_t remaining_space_caq (caq_t const *restrict caq) {
   size_t ret = caq->array.n - 1 - used_space_caq (caq);
   assert (ret <= caq->array.n - 1);
   return ret;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
size_t indexOf_caq (caq_t const *restrict caq,
	void const *restrict e) {
   /* check from head to tail */
   /* or check from head to end, then from 0 to tail */
   size_t ret;
   ssize_t r;
   array_t tmp;
   if (caq->head <= caq->tail) {
      init_array2 (&tmp, &(caq->array), caq->head,
         caq->tail - caq->head);
      return indexOf_array (&tmp, e);
   }
   init_array2 (&tmp, &(caq->array), caq->head, caq->array.n - caq->head);
   r = indexOf_array_chk (&tmp, e);
   if (r >= 0) return (size_t) r;
   init_array2 (&tmp, &(caq->array), (size_t) 0, caq->tail);
   return indexOf_array (&tmp, e);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
bool contains_caq (caq_t const *restrict caq,
	void const *restrict e) {
   array_t tmp;
   if (caq->head <= caq->tail) {
      init_array2 (&tmp, &(caq->array), caq->head,
         caq->tail - caq->head);
      return contains_array (&tmp, e);
   }
   init_array2 (&tmp, &(caq->array), caq->head, caq->array.n - caq->head);
   if (contains_array (&tmp, e)) return true;
   init_array2 (&tmp, &(caq->array), (size_t) 0, caq->tail);
   return contains_array (&tmp, e);
}

__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result))
ssize_t indexOf_caq_chk (caq_t const *restrict caq,
   void const *restrict e) {
   ssize_t ret;
   array_t tmp;
   if (caq->head <= caq->tail) {
      init_array2 (&tmp, &(caq->array), caq->head,
         caq->tail - caq->head);
      return indexOf_array_chk (&tmp, e);
   }
   init_array2 (&tmp, &(caq->array), caq->head, caq->array.n - caq->head);
   ret = indexOf_array_chk (&tmp, e);
   if (ret >= 0) return ret;
   init_array2 (&tmp, &(caq->array), (size_t) 0, caq->tail);
   ret = indexOf_array_chk (&tmp, e);
   assert (ret == (ssize_t) -1 || ret < (ssize_t) caq->array.n);
   assert (ret == (ssize_t) -1 || ret < (ssize_t) remaining_space_caq (caq));
   return ret;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void *index_caq (caq_t const *restrict caq, size_t i) {
   return index_array (&(caq->array), (caq->head + i) % caq->array.n);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void enqueues (caq_t *restrict q, void const *restrict e, size_t n) {
#ifndef NDEBUG
   size_t chk_rem  = remaining_space_caq (q);
   size_t chk_used = used_space_caq (q);
#endif
   size_t diff = q->array.n - q->tail;
   array_t tmp;
   assert (n == 0 || ! isfull (q));
   assert (remaining_space_caq (q) >= n);
   if (q->head > q->tail || n <= diff)
      sets_array (&(q->array), q->tail, e, n);
   else {
      sets_array (&(q->array), q->tail, e, diff);
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
      init_array (&tmp, e, q->array.esz, n);
	#pragma GCC diagnostic pop
      sets_array (&(q->array), (size_t) 0, /*e+diff*/index_array (&tmp, diff), n - diff);
   }
   /*
   if (q->head <= q->tail) {
      if (n <= q->array.n) {
         sets_array (&(q->array), q->tail, e, n);
      } else {
         size_t diff = q->array.n - q->tail;
         sets_array (&(q->array), q->tail, e, diff);
         sets_array (&(q->array), 0, e, n - diff);
      }
   } else {
      sets_array (&(q->array), q->tail, e, n);
   }
   */
   q->tail = (q->tail + n) % q->array.n;
   assert (chk_rem  - n == remaining_space_caq (q));
   assert (chk_used + n == used_space_caq      (q));
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void dequeues (caq_t *restrict q, void *restrict e, size_t n) {
#ifndef NDEBUG
   size_t chk_rem  = remaining_space_caq (q);
   size_t chk_used = used_space_caq (q);
#endif
   size_t diff = q->array.n - q->head;
   array_t tmp;
   assert (n == 0 || ! isempty (q));
   assert (used_space_caq (q) >= n);
   if (q->tail > q->head || n <= diff)
      gets_array (&(q->array), q->head, e, n);
   else {
      gets_array (&(q->array), q->head, e, diff);
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
      init_array (&tmp, e, q->array.esz, n);
	#pragma GCC diagnostic pop
      gets_array (&(q->array), (size_t) 0, /*e + diff*/index_array (&tmp, diff), n - diff);
   }
   q->head = (q->head + n) % q->array.n;
   assert (chk_rem  + n == remaining_space_caq (q));
   assert (chk_used - n == used_space_caq      (q));
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void frees_caq (caq_t const *restrict caq, free_t f) {
   array_t tmp;
   if (caq->head <= caq->tail) {
      init_array2 (&tmp, &(caq->array), caq->head,
         caq->head - 1 + (caq->tail - caq->head));
      frees_array (&tmp, f);
   } else {
      init_array2 (&tmp, &(caq->array), caq->head,
         caq->head - 1 + (caq->array.n - caq->head));
      frees_array (&tmp, f);
      init_array2 (&tmp, &(caq->array), (size_t) 0,
         caq->tail - 1);
      frees_array (&tmp, f);
   }
}
