#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int in_circle = 0;
int total = 10000;

void *calculate_in_circle_random_count() {
  srand((unsigned int)time(NULL));
  for (int i = 0; i < total; i++) {
    float x = (float)rand()/(float)(RAND_MAX);
    float y = (float)rand()/(float)(RAND_MAX);

    float val = sqrt((x * x) + (y * y));

    if (val < 1.0) {
      in_circle++;
    }
  }

  pthread_exit(0);
}

int main(int argc, char const *argv[]) {
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, calculate_in_circle_random_count, NULL);
  pthread_join(thread_id, NULL);

  // will continue once the thread is done
  float pi_approx = 4 * (float)in_circle / (float)total;

  printf("In circle: %d\n", in_circle);
  printf("Total: %d\n", total);
  printf("Pi approximation: %.6f\n", pi_approx);

  return 0;
}
