#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
  if (argc <= 2 || argc > 3) {
    printf("Please provide two arguments one for the source and one for the destination files.\n");
    return -1;
  }

  char parent_output[100];
  char child_output[100];

  int fd[2];
  int bytes;
  int content;
  int target;

  if (pipe(fd) != 0) {
    fprintf(stderr, "Pipes failed\n");
    return 1;
  }

  pid_t pid;

  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed");
		return 1;
  } else if (pid == 0) { // child process
    // close write end
    close(fd[1]);

    read(fd[0], child_output, sizeof(child_output));
    close(fd[0]);

    target = open(argv[2], O_CREAT |O_WRONLY, 00777);
    write(target, child_output, (strlen(child_output) - 1));

  } else { // parent
    content = open(argv[1], O_RDONLY);
    bytes = read(content, parent_output, sizeof(parent_output));

    // close read end
    close(fd[0]);

    write(fd[1], parent_output, bytes);
  }

  return 0;
}
