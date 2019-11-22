#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/*
A function that repeatedly checks the time and returns once it has run for a
second. Then, it prints out the string that the user passed in on the
command line, and repeats, forever.
*/
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: cpu <string>\n");
        exit(1);
    }

    char *str = argv[1];
    while (1) {
        Spin(1);
        printf("%s\n", str);
    }
    return 0;
}

/*
./cpu A & ./cpu B & ./cpu C & ./cpu D &
[1] 7353
[2] 7354
[3] 7355
[4] 7356
A
B
D
C
A
B
D
C
A
*/

/* Even though we have only one processor, somehow all four of these programs
seem to be running at the same time!
Turning a single CPU (or small set of them) into a seemingly infinite number
of CPUs and thus allowing many programs to seemingly run at once is what we
call virtualizing the CPU

If two programs want to run at a particular time, which should run?
This question is answered by a policy of the OS; policies are used in many
different places within an OS to answer these types of questions, */
