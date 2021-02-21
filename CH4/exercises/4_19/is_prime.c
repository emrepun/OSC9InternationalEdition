#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void is_prime(int test) {
    if (test < 2)
      return;
    for(int i= 2; i * i <= test; i++) {
        if(test % i == 0) {
            return;
        }
    }
    printf("%d\n",test);
}

void *print_primes_until(void *arg) {
  int *limit = (int *) arg;

  for (int i = 0; i <= *limit; i++) {
    is_prime(i);
  }
  pthread_exit(0);
}

int main(int argc, char const *argv[]) {
  int numb = 0;

  if (argc > 1)
      numb = atoi(argv[1]);

  pthread_t thread_id;
  pthread_create(&thread_id, NULL, print_primes_until, &numb);
  pthread_join(thread_id, NULL);

  return 0;
}
