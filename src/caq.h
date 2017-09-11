#ifndef _CAQ_H_
#define _CAQ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

typedef struct {
	void *restrict Q;
	size_t esz;
	size_t n;
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
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;
void free_queue (caq_t *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

/* ret type == elem type */
void *dequeue (caq_t *restrict q)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;

/* returns err code */
void *enqueue (caq_t *restrict q)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;

bool isempty (caq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

bool isfull (caq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

void *gethead (caq_t const *restrict q)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

void dumpq(caq_t const *restrict q, int i)
__attribute__ ((nonnull (1), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _CAQ_H_ */