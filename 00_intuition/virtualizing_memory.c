#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char * argv[]) {
  int *p = malloc(sizeof(int));
  assert(p != NULL);
  printf("(%d) address pointed to by p: %p\n", getpid(), p);
  *p = 0;
  while (1) {
    Spin(1);
    *p = *p + 1;
    printf("(%d) p: %d\n", getpid(), *p);
  }
  return 0;
}

// ./a.out &; ./a.out
// (8743) address pointed to by p: 0x7ff99bc02d70
// (8744) address pointed to by p: 0x7ffca6c02d70
// (8743) p: 1
// (8744) p: 1
// (8743) p: 2
// (8744) p: 2
// (8743) p: 3
// (8744) p: 3
// (8743) p: 4
// (8744) p: 4
// (8743) p: 5
// (8744) p: 5


// We see from the example that each running
// program has allocated memory at the same address (0x7ff99bc02d70), and yet
// each seems to be updating the value at 0x7ff99bc02d70 independently! It is as
// if each running program has its own private memory, instead of sharing
// the same physical memory with other running programs5
// .
// Indeed, that is exactly what is happening here as the OS is virtualizing memory.
// Each process accesses its own private virtual address space
// (sometimes just called its address space), which the OS somehow maps
// onto the physical memory of the machine. A memory reference within
// one running program does not affect the address space of other processes
// (or the OS itself); as far as the running program is concerned, it has
// physical memory all to itself. The reality, however, is that physical memory is
// a shared resource, managed by the operating system.
