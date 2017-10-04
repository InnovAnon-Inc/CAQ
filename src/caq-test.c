#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <mmalloc.h>
#include <simon.h>

#include <caq.h>

__attribute__ ((nonnull (1), nothrow))
static void dumpq(caq_t const *restrict q) {
   size_t i;
   fputs ("Q: ", stderr);
   for (i = 0; i != used_space_caq (q); i++) {
      void *restrict head = index_caq (q, i);
      fprintf (stderr, "(%1d:%3d), ", (int) i, *(int *restrict) head);
   }
   fputs ("\n", stderr);
}

typedef struct {
   size_t esz;
   size_t n;
} alloc_t;

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static void *caq_alloc (void const *restrict arg_) {
   alloc_t const *restrict arg = (alloc_t const *restrict) arg_;
   return ez_alloc_caq (arg->esz, arg->n);
}

__attribute__ ((nonnull (1), nothrow))
static void generate_int (void *restrict arg_) {
   int *restrict arg = (int *restrict) arg_;
   *arg = random_range_java (-10, 10);
}

__attribute__ ((nonnull (1), nothrow))
static void generates_int (void *restrict arg_, size_t n) {
   int *restrict arg = (int *restrict) arg_;
   size_t i;
   for (i = 0; i != n; i++)
      arg[i] = random_range_java (-10, 10);
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_add_test (void *restrict arg_) {
   int tmp;
   int err;
   error_check (add_test (arg_, &tmp,
      (isfull_t) isfull, generate_int, (add_t) enqueue) != 0)
      return -1;
   fprintf (stderr, "caq_add_test (), tmp:%d\n", tmp);
   dumpq ((caq_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_remove_test (void *restrict arg_) {
   int tmp;
   error_check (remove_test (arg_, &tmp,
      (isempty_t) isempty, (remove_t) dequeue) != 0)
      return -1;
   fprintf (stderr, "caq_remove_test (), tmp:%d\n", tmp);
   dumpq ((caq_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_adds_test (void *restrict arg_) {
   int tmps[10];
   error_check (adds_test (arg_, tmps, ARRSZ (tmps),
      (remaining_space_t) remaining_space_caq,
      caq_generates, (adds_t) enqueues) != 0)
      return -1;
   /* can't print tmps, because we don't know how many elements are init'd */
   fprintf (stderr, "caq_adds_test ()\n");
   dumpq ((caq_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_removes_test (void *restrict arg_) {
   int tmps[10];
   error_check (removes_test (arg_, tmps, ARRSZ (tmps),
      (used_space_t) used_space_caq, (removes_t) dequeues) != 0)
      return -1;
   /* can't print tmps, because we don't know how many elements are init'd */
   fprintf (stderr, "caq_removes_test ()\n");
   dumpq ((caq_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_cb (void *restrict arg) {
   stdcb_t tests[4];

   TODO (more tests)
   tests[0] = caq_add_test;
   tests[1] = caq_remove_test;
   tests[2] = caq_adds_test;
   tests[3] = caq_removes_test;
   /*assert (ARRSZ (tests) == 2);*/


   error_check (random_ops (arg, tests, ARRSZ (tests), 100) != 0)
   /*random_ops2 (arg, tests, ARRSZ (tests));*/
      return -1;

   /*return 0;*/
}

__attribute__ ((nonnull (1), nothrow))
static void caq_free (void *restrict arg_) {
   caq_t *restrict arg = (caq_t *restrict) arg_;
   /* frees_caq () */
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

#ifdef TESTING
   caq_t tmp;
   int i, j, k;
   int N[10];

   error_check (alloc_queue (&tmp, sizeof (int), (size_t) 10) != 0) return -1;





/*
   for (k = 1; k != 20; k++) {
      for (i = 0; i != 10 - 10 % k; i++) {
         assert (remaining_space_caq (&tmp) == (size_t) (10 - i));
         assert (used_space_caq (&tmp) == (size_t) i);
         enqueue (&tmp, &i);
         assert (remaining_space_caq (&tmp) == (size_t) (10 - i - 1));
         assert (used_space_caq (&tmp) == (size_t) (i + 1));
      }
      assert (10 % k != 0 || isfull (&tmp));
      assert (remaining_space_caq (&tmp) == (size_t) (10 - (10 - 10 % k)));
      assert (used_space_caq (&tmp) == (size_t) ((10 - 10 % k) - 0));
      for (i = 0; i != 10 - 10 % k; i++) {
         assert (remaining_space_caq (&tmp) == (size_t) i);
         assert (used_space_caq (&tmp) == (size_t) (10 - i));
         dequeue (&tmp, &j);
         assert (j == i);
         assert (remaining_space_caq (&tmp) == (size_t) (i + 1));
         assert (used_space_caq (&tmp) == (size_t) (10 - i - 1));
      }
      assert (isempty (&tmp));
      assert (remaining_space_caq (&tmp) == (size_t) 10);
      assert (used_space_caq (&tmp) == (size_t) 0);
   }
*/

   for (i = 0; i != 10; i++) {
         assert (remaining_space_caq (&tmp) == (size_t) (10 - i));
         assert (used_space_caq (&tmp) == (size_t) i);
         enqueue (&tmp, &i);
         dumpq (&tmp);
         assert (remaining_space_caq (&tmp) == (size_t) (10 - i - 1));
         assert (used_space_caq (&tmp) == (size_t) (i + 1));
      }
      assert (isfull (&tmp));
      assert (remaining_space_caq (&tmp) == (size_t) (0));
      assert (used_space_caq (&tmp) == (size_t) (10));
      for (i = 0; i != 10; i++) {
         assert (remaining_space_caq (&tmp) == (size_t) i);
         assert (used_space_caq (&tmp) == (size_t) (10 - i));
         dequeue (&tmp, &j);
         dumpq (&tmp);
         assert (j == i);
         assert (remaining_space_caq (&tmp) == (size_t) (i + 1));
         assert (used_space_caq (&tmp) == (size_t) (10 - i - 1));
      }
      assert (isempty (&tmp));
      assert (remaining_space_caq (&tmp) == (size_t) 10);
      assert (used_space_caq (&tmp) == (size_t) 0);

      for (i = 0; i != 10; i++)
         N[i] = i;

      enqueues (&tmp, N, (size_t) 10);
      dumpq (&tmp);
      assert (isfull (&tmp));
      assert (remaining_space_caq (&tmp) == (size_t) (0));
      assert (used_space_caq (&tmp) == (size_t) (10));
      dequeues (&tmp, N, (size_t) 10);
      dumpq (&tmp);
      assert (isempty (&tmp));
      assert (remaining_space_caq (&tmp) == (size_t) 10);
      assert (used_space_caq (&tmp) == (size_t) 0);

      for (i = 0; i != 10; i++)
         assert (N[i] == i);

   free_queue (&tmp);
#endif
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

