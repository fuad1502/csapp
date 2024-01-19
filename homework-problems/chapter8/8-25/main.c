#include <setjmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

__sighandler_t Signal(int sig, __sighandler_t handler);

jmp_buf env;
void handler(int sig) { siglongjmp(env, 0); }

char *tfgets(char *s, int n, FILE *stream) {
  Signal(SIGUSR1, handler);
  if (fork() == 0) {
    sleep(5);
    kill(getppid(), SIGUSR1);
    exit(0);
  }
  if (sigsetjmp(env, SIGUSR1) == 0) {
    return fgets(s, n, stream);
  } else {
    return NULL;
  }
}

int main(int argc, char *argv[]) {
  char s[100];
  int n = 100;
  char *ret_s = tfgets(s, n, stdin);
  if (ret_s) {
    printf("%s\n", ret_s);
  } else {
    printf("Timeout exceeded: returned NULL\n");
  }
  return 0;
}

__sighandler_t Signal(int sig, __sighandler_t handler) {
  struct sigaction action, old_action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = SA_RESTART;
  sigaction(sig, &action, &old_action);
  return old_action.sa_handler;
}
