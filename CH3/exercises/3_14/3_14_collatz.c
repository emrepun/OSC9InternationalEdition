#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ctype.h>


void collatz(int val) {
  printf("%i\n", val);

  if (val == 1) {
    return;
  }

  if (val % 2 == 0) {
    int newVal = val / 2;
    collatz(newVal);
  } else {
    int newVal = (val * 3) + 1;
    collatz(newVal);
  }
}

int main(int argc, char *argv[]) {
  if (argc <= 1 || argc > 2) {
    printf("Please only provide one positive integer argument\n");
    return -1;
  }
  int val = atoi(argv[1]);

  // either non int value or negative integer, which we do not support.
  if (val <= 0) {
    printf("Invalid argument, please provide a positive integer value\n");
    return 1;
  }

  pid_t pid;

  pid = fork();

  if (pid == 0) { // child process
    printf("CHILD\n");
    collatz(val);
  } else if (pid > 0) { // parent process
    wait(NULL);
    printf("PARENT\n");
  }

}
