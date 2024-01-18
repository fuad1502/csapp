#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_SH_CMD_STR 100

extern char **environ;

void unix_error(char *msg);
pid_t Fork();
int mysystem(char *command);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./mysystem <command>\n");
    exit(1);
  }
  int ret = system(argv[1]);
  printf("Return: %d\n", ret);
  ret = mysystem(argv[1]);
  printf("Return: %d\n", ret);
  return 0;
}

int mysystem(char *command) {
  pid_t pid;
  if ((pid = fork()) == 0) {
    // Child
    char shell_command[MAX_SH_CMD_STR];
    strcpy(shell_command, "/bin/sh -c ");
    strcat(shell_command, command);
    strcat(shell_command, " ");
    char *arguments[4];
    arguments[0] = "/bin/sh";
    arguments[1] = "-c";
    arguments[2] = command;
    arguments[3] = 0;
    if (execve("/bin/sh", arguments, environ) < 0) {
      unix_error("Execve error");
    }
  }
  // Parent
  int status;
  if (waitpid(pid, &status, 0) > 0) {
    if (WIFEXITED(status)) {
      return WEXITSTATUS(status);
    }
  }
  return -1;
}

pid_t Fork() {
  pid_t pid;
  if ((pid = fork()) == -1) {
    unix_error("Call to fork failed");
  }
  return pid;
}

void unix_error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}
