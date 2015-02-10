#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  /* sleep(1) */
#include <signal.h>

void ex_program(int sig);

int main(void) {
  (void) signal(SIGINT, ex_program);
  
  while(1)
    printf("sleeping .. ZZZzzzz ....\n"), sleep(1);
  
  return 0;
}

void ex_program(int sig) {
  printf("Wake up call ... !!! - Catched signal: %d ... !!\n", sig);
  exit(EXIT_SUCCESS);
  // (void) signal(SIGINT, SIG_DFL);
}

