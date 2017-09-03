#include <stdio.h>
#include <stdlib.h>

#include "caq.h"

#define N (4)

int main() {
   caq_t q;
   alloc_queue (&q, N);

   dumpq(&q, 1);
   enqueue(&q, 101);dumpq(&q, 2);
   enqueue(&q, 202);dumpq(&q, 3);
   enqueue(&q, 303);dumpq(&q, 4);
   enqueue(&q, 404);dumpq(&q, 5);
   enqueue(&q, 505);dumpq(&q, 6);
   printf("%i\n", dequeue(&q));
      dumpq(&q, 7);
   printf("%i\n", dequeue(&q));
      dumpq(&q, 8);
   printf("%i\n", dequeue(&q));
      dumpq(&q, 9);
   printf("%i\n", dequeue(&q));
      dumpq(&q, 10);
   printf("%i\n", dequeue(&q));
      dumpq(&q, 11);

   free_queue (&q);
   return EXIT_SUCCESS;
}