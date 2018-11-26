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
  int status,f,cpid;
  char ** args = parse_args( argc, *argv );
  
  f = fork();
  
  if (!f){
    printf("Child executing\n");
    execvp(args[1], argv);
    printf("Error executing\n");
  }else if(f > 0){

    if((cpid = wait(&status)) < 0){
      printf("Waiting");
      exit(1);
    }

    printf("Parent: Complete\n");
  }else{
    printf("Fork failed\n");
    exit(1);
  }
  return 0;
}
