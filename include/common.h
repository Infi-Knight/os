#ifndef __common_h__
#define __common_h__

#include <sys/time.h> // gettimeofday()
#include <sys/stat.h>
#include <assert.h>

/* Returns the total time passed since Unix epoch in seconds */
double GetTime() {
    struct timeval t;

    int rc = gettimeofday(&t, NULL); // populate timeval struct (man 2 gettimeofday)
    assert(rc == 0);

    return (double) t.tv_sec + (double) t.tv_usec/1e6;
}

void Spin(int howlong) {
    double t = GetTime();
    while ((GetTime() - t) < (double) howlong)
        ;
}

#endif // __common_h__
