#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <simon.h>

#include <caq.h>

typedef __attribute__ ((warn_unused_result))
void *(*do_alloc_t) (void *restrict) ;

typedef __attribute__ ((nonnull (1)))
void (*do_free_t) (void *restrict) ;

__attribute__ ((/*leaf,*/ nonnull (1, 3, 4), nothrow, warn_unused_result))
static int ezmalloc (do_alloc_t do_alloc, void *restrict alloc_args,
   stdcb_t cb, do_free_t do_free) {
   void *restrict ds = do_alloc (alloc_args);
   error_check (ds == NULL) return -1;
   error_check (cb (ds) != 0) return -2;
   do_free (ds);
   return 0;
}

typedef struct {
   size_t esz;
   size_t n;
} alloc_t;

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static void *caq_alloc (void *restrict arg_) {
   alloc_t *restrict arg = (alloc_t *restrict) arg_;
   return ez_alloc_caq (arg->esz, arg->n);
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_add_test (void *restrict arg_) {
   caq_t *restrict arg = (caq_t *restrict) arg_;
   int tmp;
   if (isfull (arg)) return 0;
   tmp = random_range_java (-10, 10);
   enqueue (arg, &tmp);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_remove_test (void *restrict arg_) {
   caq_t *restrict arg = (caq_t *restrict) arg_;
   int tmp;
   if (isempty (arg)) return 0;
   dequeue (arg, &tmp);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_adds_test (void *restrict arg_) {
   caq_t *restrict arg = (caq_t *restrict) arg_;
   int tmps[10];
   size_t i;
   size_t n;
#ifdef TEST
   fprintf (stderr, "caq_adds_test\n");
   n = min (ARRSZ (tmps), remaining_space_caq (arg));
   /*if (n == 0) return 0;*/
   if (n != 0)
      n = random_range_java_size_t2 ((size_t) 0, n);
   ez_random_ranges (tmps, n, -10, 10);
   enqueues (arg, tmps, n);
#endif
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_removes_test (void *restrict arg_) {
   caq_t *restrict arg = (caq_t *restrict) arg_;
   int tmps[10];
   size_t n;
#ifdef TEST
   fprintf (stderr, "caq_removes_test\n");
   n = min (ARRSZ (tmps), used_space_caq (arg));
   /*if (n == 0) return 0;*/
   if (n != 0)
      n = random_range_java_size_t2 ((size_t) 0, n);
   dequeues (arg, tmps, n);
#endif
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_cb (void *restrict arg_) {
   caq_t *restrict arg = (caq_t *restrict) arg_;
   unsigned int ntest = 10;
   unsigned int i;
   size_t j;
   stdcb_t tests[2];

   TODO (more tests)
   tests[0] = caq_add_test;
   tests[1] = caq_remove_test;
   /*tests[2] = caq_adds_test;
   tests[3] = caq_removes_test;*/
   /*assert (ARRSZ (tests) == 2);*/

   for (i = 0; i != ntest; i++) {
      j = random_range_java_size_t2 ((size_t) 0, ARRSZ (tests) - 1);
      assert (j <= ARRSZ (tests));
      /*assert (j != 0 || tests[j] == caq_add_test);
      assert (j != 1 || tests[j] == caq_remove_test);
      assert (j == 0 || j == 1);*/
      error_check (tests[j] (arg) != 0) return -1;
   }

   return 0;
}

__attribute__ ((nonnull (1), nothrow))
static void caq_free (void *restrict arg_) {
   caq_t *restrict arg = (caq_t *restrict) arg_;
   ez_free_caq (arg);
}








/*#define N (4)*/

int main(void) {
#ifdef TEST
   int arr[] = {101, 202, 303, 404, 505};
   int *tmp;

   caq_t q;
   error_check (alloc_queue (&q, sizeof (int), (size_t) N) != 0)
      return EXIT_FAILURE;

   dumpq(&q, 1);
   *(int*)enqueue(&q) = arr[0];dumpq(&q, 2);
   *(int*)enqueue(&q) = arr[1];dumpq(&q, 3);
   *(int*)enqueue(&q) = arr[2];dumpq(&q, 4);
   tmp = enqueue(&q);
   if (tmp != NULL) *tmp = arr[3];
   dumpq(&q, 5);
   tmp = enqueue(&q);
   if (tmp != NULL) *tmp= arr[4];
   dumpq(&q, 6);
   memset (arr, 0, sizeof (arr));
   printf("%i\n", *(int *) dequeue(&q));
      dumpq(&q, 7);
   printf("%i\n", *(int *) dequeue(&q));
      dumpq(&q, 8);
   printf("%i\n", *(int *) dequeue(&q));
      dumpq(&q, 9);
   tmp = (int *) dequeue (&q);
   if (tmp == NULL) puts ("NULL");
   else printf("%i\n", *tmp);
      dumpq(&q, 10);
   tmp = (int *) dequeue (&q);
   if (tmp == NULL) puts ("NULL");
   else printf ("%i\n", *tmp);
      dumpq(&q, 11);

   free_queue (&q);
#endif


   time_t t;
   alloc_t alloc_arg;
   caq_t tmp;

   int i;
   error_check (alloc_queue (&tmp, sizeof (int), (size_t) 10) != 0) return -1;
   for (i = 0; i != 10; i++) {
      assert (remaining_space_caq (&tmp) == (size_t) (10 - i));
      enqueue (&tmp, &i);
      assert (remaining_space_caq (&tmp) == (size_t) (10 - i - 1));
   }
   free_queue (&tmp);

   t = time (NULL);
   srand ((unsigned int) t);

   alloc_arg.esz = sizeof (int);
   alloc_arg.n   = 10;

   error_check (ezmalloc (caq_alloc, &alloc_arg, caq_cb, caq_free) != 0)
      return -1;

/*
   wtf = caq_alloc (&alloc_arg);
   error_check (wtf == NULL) return -1;
   error_check (caq_cb (wtf) != 0) return -2;
   caq_free (wtf);
*/
/*
   wtf = ez_alloc_caq (sizeof (int), (size_t) 10);
   error_check (wtf == NULL) return -1;
   ez_free_caq (wtf);
*/
   return EXIT_SUCCESS;
}

