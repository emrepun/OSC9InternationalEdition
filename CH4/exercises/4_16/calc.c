#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int average;
int min;
int max;
int size = 0;

void *average_of_array(void *arg) {
  int *numbers = (int *) arg;
  int sum;
  for (int i = 0; i < size; i++) {
    printf("Numb is: %i\n", numbers[i]);
    sum += numbers[i];
  }
  average = sum / size;
  pthread_exit(0);
}


void *min_of_array(void *arg) {
  int *numbers = (int *) arg;
  if (size < 1) {
    min = 0;
    pthread_exit(0);
  }
  min = numbers[0];
  for (int i = 0; i < size; i++) {
    if (min > numbers[i]) {
      min = numbers[i];
    }
  }
  pthread_exit(0);
}

void *max_of_array(void *arg) {
  int *numbers = (int *) arg;
  if (size < 1) {
    max = 0;
    pthread_exit(0);
  }
  max = numbers[0];
  for (int i = 0; i < size; i++) {
    if (max < numbers[i]) {
      max = numbers[i];
    }
  }
  pthread_exit(0);
}

int main(int argc, char const *argv[]) {
  size = argc - 1;
  int numbers[size];
  int numbers2[size];
  int numbers3[size];

  for (int i = 0; i < size; i++) {
    int num;
    sscanf(argv[i + 1], "%d", &num);
    numbers[i] = num;
    numbers2[i] = num;
    numbers3[i] = num;
  }

  int thread_count = 3;

  pthread_t id[thread_count];

  pthread_create(&id[0], NULL, average_of_array, &numbers);
  pthread_create(&id[1], NULL, min_of_array, &numbers2);
  pthread_create(&id[2], NULL, max_of_array, &numbers3);

  for (int i = 0; i < thread_count; i++) {
    pthread_join(id[i], NULL);
  }

  printf("Average is: %d\n", average);
  printf("Min is: %d\n", min);
  printf("Max is: %d\n", max);

  return 0;
}
