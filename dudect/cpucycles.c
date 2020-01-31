#include "cpucycles.h"
#include <stdint.h>
#include <time.h>

// XXX call also cpuid?
// cf
// http://www.intel.com/content/www/us/en/embedded/training/ia-32-ia-64-benchmark-code-execution-paper.html
int64_t cpucycles(void)
{
    /*
       struct timespec spec;
       clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &spec);
       return spec.tv_sec*1e9+spec.tv_nsec;
   */
    unsigned int hi, lo;
    __asm__ volatile("rdtsc\n\t" : "=a"(lo), "=d"(hi));
    return ((int64_t) lo) | (((int64_t) hi) << 32);
}
