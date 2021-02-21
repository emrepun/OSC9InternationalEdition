#include <stdio.h>
#include <stdlib.h>

double calculate_in_circle_random_count(void)
{
    static const unsigned total = 100000;
    unsigned in_circle = 0;

    #pragma omp parallel for reduction(+:in_circle)
    {
      for (unsigned i = 0;  i < total;  ++i) {
          double x = (double)rand() / RAND_MAX;
          double y = (double)rand() / RAND_MAX;

          double val = x * x + y * y;
          in_circle +=  val < 1.0;
      }
    }
    return 4.0 * in_circle / total;
}

int main(void)
{
    const double pi_approx = calculate_in_circle_random_count();
    printf("Pi approximation: %.6f\n", pi_approx);

}
