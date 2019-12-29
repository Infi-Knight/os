#include <stdio.h>
#include <stdlib.h>
#include "common_threads.h"

volatile int counter = 0;
int loops;

void *worker(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    counter++;
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Provide an integer value\n");
    exit(1);
  }

  loops = atoi(argv[1]);
  pthread_t p1, p2;
  printf("Initial value: %d\n", counter);

  Pthread_create(&p1, NULL, worker, NULL);
  Pthread_create(&p2, NULL, worker, NULL);
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  printf("Final value : %d\n", counter);
  return 0;
}

// ➜ ./a.out 1000
// Initial value: 0
// Final value : 2000

// ➜ ./a.out 565665
// Initial value: 0
// Final value : 785615

// ➜ ./a.out 100000
// Initial value: 0
// Final value : 109002

// ➜ ./a.out 100000
// Initial value: 0
// Final value : 104180

// In this run, when we gave an input value of 100,000, instead of getting
// a final value of 200,000, we instead first get 109002. Then, when we run
// the program a second time, we not only again get the wrong value, but
// also a different value than the last time. In fact, if you run the program
// over and over with high values of loops, you may find that sometimes
// you even get the right answer! So why is this happening?

// As it turns out, the reason for these odd and unusual outcomes relate
// to how instructions are executed, which is one at a time. Unfortunately, a
// key part of the program above, where the shared counter is incremented,
// takes three instructions:
// - one to load the value of the counter from memory into a register,
// - one to increment it, and
// - one to store it back into memory.
// Because these three instructions do not execute atomically (all at
// once), strange things can happen.
