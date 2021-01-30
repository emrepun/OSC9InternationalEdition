#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <ctype.h>
#include <string.h>


int collatz_step(int val) {
  if (val == 1 || val == 0) {
    return val;
  }

  if (val % 2 == 0) {
    return val / 2;
  } else {
    return (val * 3) + 1;
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

  const int SIZE = 4096;
	const char *name = "OS";

  int shm_fd;
	void *ptr;

  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  ftruncate(shm_fd, SIZE);

  ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    printf("Map failed\n");
    return -1;
  }

  pid_t pid;

  pid = fork();

  if (pid == 0) { // child process
    printf("CHILD\n");
    while (val != 1) {
      val = collatz_step(val);
      ptr+= sprintf(ptr, "%i", val);
      ptr+= sprintf(ptr, " ");
    }
  } else if (pid > 0) { // parent process
    wait(NULL);
    printf("PARENT\n");

    printf("%s", ptr);
  }

}
