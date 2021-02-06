#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 4096
#define READ_END	0
#define WRITE_END	1

void reverseCase(char *char_array_pointer) {
  int count = 0;

  while(char_array_pointer[count] != '\0') {
    if (isupper(char_array_pointer[count])) {
      char_array_pointer[count] = tolower(char_array_pointer[count]);
    } else {
      char_array_pointer[count] = toupper(char_array_pointer[count]);
    }
    count++;
  }
}

int main(int argc, char const *argv[]) {
  char write_msg_parent[BUFFER_SIZE] = "Hi There";
  char read_msg_parent[BUFFER_SIZE];

  char write_msg_child[BUFFER_SIZE];
  char read_msg_child[BUFFER_SIZE];
  pid_t pid;

  // create two pipes:
  // - parent_fd used by parent to write to child
  // - child_fd used by child to write to parent
  int parent_fd[2], child_fd[2];

  if (pipe(parent_fd) != 0 || pipe(child_fd) != 0) {
    fprintf(stderr, "Pipes failed\n");
    return 1;
  }

  /* fork a child process */
	pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed");
		return 1;
  } else if (pid == 0) { // child process
    printf("Reached to child\n");
    close(child_fd[READ_END]);
    close(parent_fd[WRITE_END]);

    int n = read(parent_fd[READ_END], read_msg_parent, sizeof(read_msg_parent) - 1);
    read_msg_parent[n] = '\0';
    printf("Child read from parent pipe: %s\n", read_msg_parent);
    close(parent_fd[READ_END]);

    strcpy(write_msg_child, read_msg_parent);
    reverseCase(write_msg_child);

    write(child_fd[WRITE_END], write_msg_child, strlen(write_msg_child));
    close(child_fd[WRITE_END]);
    printf("Child writing to pipe: %s\n", write_msg_child);
  } else { // parent process
    // write to child
    close(parent_fd[READ_END]);
    close(child_fd[WRITE_END]);

    printf("Parent writing to pipe: %s\n", write_msg_parent);
    write(parent_fd[WRITE_END], write_msg_parent, strlen(write_msg_parent));

    close(parent_fd[WRITE_END]);

    // read from child
    int n = read(child_fd[READ_END], read_msg_child, sizeof(read_msg_child) - 1);
    read_msg_child[n] = '\0';
    close(child_fd[READ_END]);

    printf("Parent read from child: %s\n", read_msg_child);
  }

  int corpse;
  int status;

  while ((corpse = wait(&status)) > 0) {
    printf("Child process exited");
  }

  return 0;
}
