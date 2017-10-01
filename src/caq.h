#ifndef _CAQ_H_
#define _CAQ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>
#include <array.h>

typedef struct {
	array_t array;
	size_t head;
	size_t tail;
} caq_t;

void init_queue (
	caq_t *restrict q,
	void *restrict arr,
	size_t esz, size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

int alloc_queue (
	caq_t *restrict q,
	size_t esz, size_t n)
__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result)) ;

void free_queue (caq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void dequeue (caq_t *restrict q, void *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void enqueue (caq_t *restrict q, void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

int dequeue_chk (caq_t *restrict q, void *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result)) ;

int enqueue_chk (caq_t *restrict q, void const *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result)) ;

bool isempty (caq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

bool isfull (caq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

void *gethead (caq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result)) ;

void *gethead_chk (caq_t const *restrict q)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

void *gettail (caq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result)) ;

void *gettail_chk (caq_t const *restrict q)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

TODO (enqueues())
TODO (dequeues())

/*
void dumpq(caq_t const *restrict q, int i)
__attribute__ ((nonnull (1), nothrow)) ;
*/

size_t caqsz (size_t esz, size_t n)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

size_t caqsz2 (caq_t const *restrict caq)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

caq_t *ez_alloc_caq (size_t esz, size_t maxn)
__attribute__ ((nothrow, warn_unused_result)) ;

void ez_free_caq (caq_t *restrict caq)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

size_t used_space_caq (caq_t const *restrict caq)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

size_t remaining_space_caq (caq_t const *restrict caq)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _CAQ_H_ */