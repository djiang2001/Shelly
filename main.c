#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

char ** parse_args(int nargs,char * line ) {
  char ** a = malloc(nargs * sizeof(char *));
  int i = 0;
  while(i < nargs) {
    a[i] = strsep(&line, " ");
    i++;
  }
  return a;
}

int main(int argc, char * argv[]){
  char ** args = parse_args( argc, *argv );
  int f = fork();
  int status;
  int cpid = wait(&status);
  if (!f){
    exit(execvp(args[0], args));
  }
  if(WIFEXITED(status))
    //printf("%d \n",WEXITSTATUS(status));
  return 0;
}
