#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 2

void unix_error(char *msg);
int Fork();

void handler(int sig) {}

int main() {
  int status, i;
  pid_t pid;

  /* Parent creates N children */
  for (i = 0; i < N; i++)
    if ((pid = Fork()) == 0) { /* Child */
      int *p = NULL;
      *p = i;
      exit(0);
    }

  /* Parent reaps N children in no particular order */
  while ((pid = waitpid(-1, &status, 0)) > 0) {
    if (WIFEXITED(status))
      printf("child %d terminated normally with exit status=%d\n", pid,
             WEXITSTATUS(status));
    else if (WIFSIGNALED(status)) {
      int sig = WTERMSIG(status);
      char msg[100];
      psignal(sig, msg);
      printf("child %d terminated by signal %d: %s\n", pid, sig, msg);
    } else
      printf("child %d terminated abnormally\n", pid);
  }

  /* The only normal termination is if there are no more children */
  if (errno != ECHILD)
    unix_error("waitpid error");

  exit(0);
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
