#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

typedef unsigned long long rand_state;

// multiplier/modulus taken from Knuth Volume 2, Table 1
static const int multiplier = 314159269;
static const int addend = 1;
static const int modulus = 0x7fffffff;

#define OMP_RAND_MAX 0x7fffffff

// note that this works differently from srand, returning a seed rather than setting
// a hidden seed.
rand_state omp_srand() {
    rand_state state = time(NULL);
    state ^= (unsigned long long)omp_get_thread_num() << 32;
    return state;
}

int omp_rand(rand_state *state) {
    *state = *state * multiplier + addend;
    return *state & modulus;
}

double calculate_in_circle_random_count(void) {

    static const unsigned total = 1000000;
    unsigned in_circle = 0;

#pragma omp parallel reduction(+:in_circle)
    {
        // do per-thread initialization
        rand_state seed = omp_srand();
        int count = total / omp_get_num_threads();
        int i;

        // then do this thread's portion of the computation:
        for (i = 0;  i < count;  ++i) {

            double x = (double)omp_rand(&seed) / OMP_RAND_MAX;
            double y = (double)omp_rand(&seed) / OMP_RAND_MAX;

            double val = x * x + y * y;
            in_circle +=  val < 1.0;
        }
    }
    return 4.0 * in_circle / total;
}

int main(int argc, char const *argv[])
{
    int num_threads = 1;

    if (argc > 1)
        num_threads = atoi(argv[1]);

    omp_set_num_threads(num_threads);

    float pi_approx = calculate_in_circle_random_count();

    printf("Pi approximation: %.6f\n", pi_approx);

    return 0;
}
