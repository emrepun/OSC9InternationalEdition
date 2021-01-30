#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


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
  int val = atoi(argv[1]);
  collatz(val);

  pid_t pid;

  pid = fork();

  if (pid == 0) { // child process
    printf("CHILD");
    collatz(val);
  } else if (pid > 0) { // parent process
    wait(NULL);
    printf("PARENT");
  }

}
