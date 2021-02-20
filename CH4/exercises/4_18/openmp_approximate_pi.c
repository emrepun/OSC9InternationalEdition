#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <omp.h>

int in_circle = 0;
int total = 10000;
int thread_numb = 4;

void calculate_in_circle_random_count() {
  srand((unsigned int)time(NULL));
  for (int i = 0; i < total / thread_numb; i++) {
    float x = (float)rand()/(float)(RAND_MAX);
    float y = (float)rand()/(float)(RAND_MAX);

    float val = (x * x) + (y * y);

    if (val < 1.0) {
      #pragma omp critical
      {
        in_circle++;
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  #pragma omp parallel num_threads(thread_numb)
  {
    printf("Hello from process: %d\n", omp_get_thread_num());
    calculate_in_circle_random_count();
  }

  float pi_approx = 4 * (float)in_circle / (float)total;

  printf("In circle: %d\n", in_circle);
  printf("Total: %d\n", total);
  printf("Pi approximation: %.6f\n", pi_approx);

  return 0;
}
