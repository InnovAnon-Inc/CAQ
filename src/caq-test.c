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
} caq_alloc_t;

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static void *caq_alloc (void const *restrict arg_) {
   caq_alloc_t const *restrict arg = (caq_alloc_t const *restrict) arg_;
   return ez_alloc_caq (arg->esz, arg->n);
}

__attribute__ ((nonnull (1), nothrow))
static void generate_int (void *restrict arg_) {
   int *restrict arg = (int *restrict) arg_;
   *arg = random_range_java (-10, 10); /* arbitrary params */
}

__attribute__ ((nonnull (1), nothrow))
static void generates_int (void *restrict arg_, size_t n) {
   int *restrict arg = (int *restrict) arg_;
   size_t i;
   for (i = 0; i != n; i++)
      arg[i] = random_range_java (-10, 10); /* arbitrary params */
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_add_test (void *restrict arg_) {
   int tmp;
   int err = add_test (arg_, &tmp,
      (isfull_t) isfull, generate_int, (add_t) enqueue);
   if (err == TEST_NA) return 0;
   error_check (err != 0) return -1;
   fprintf (stderr, "caq_add_test (), tmp:%d\n", tmp);
   dumpq ((caq_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_remove_test (void *restrict arg_) {
   int tmp;
   int err = remove_test (arg_, &tmp,
      (isempty_t) isempty, (remove_t) dequeue);
   if (err == TEST_NA) return 0;
   error_check (err != 0) return -1;
   fprintf (stderr, "caq_remove_test (), tmp:%d\n", tmp);
   dumpq ((caq_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_adds_test (void *restrict arg_) {
   int tmps[13]; /* arbitrary params */
   error_check (adds_test (arg_, tmps, ARRSZ (tmps),
      (remaining_space_t) remaining_space_caq,
      generates_int, (adds_t) enqueues) != 0)
      return -1;
   /* can't print tmps, because we don't know how many elements are init'd */
   fprintf (stderr, "caq_adds_test ()\n");
   dumpq ((caq_t *restrict) arg_);
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
static int caq_removes_test (void *restrict arg_) {
   int tmps[12]; /* arbitrary params */
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

   error_check (random_ops (arg, tests, ARRSZ (tests), 100) != 0) /* arbitrary params */
   /*random_ops2 (arg, tests, ARRSZ (tests));*/
      return -1;

   return 0;
}

int main(void) {
   time_t t;
   caq_alloc_t alloc_arg;

   t = time (NULL);
   srand ((unsigned int) t);

   alloc_arg.esz = sizeof (int);
   alloc_arg.n   = 10; /* arbitrary params */

   error_check (ezmalloc (caq_alloc, &alloc_arg,
      caq_cb,
      (free_t) ez_free_caq) != 0)
      return EXIT_FAILURE;

   return EXIT_SUCCESS;
}
