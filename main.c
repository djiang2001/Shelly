#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

char ** parse_args(int nargs,char * line ) {
  char ** a = malloc(nargs * sizeof(char *));
  int i = 0;
  while(line) {
    a[i] = strsep(&line, " ");
    i++;
  }
  return a;
}

int main(){
  int status, f, cpid, nargs;
  char *s;
  fgets(s, 100, stdin);
  for(int i = 0; s[i]; i++){
    if(!(strcmp(s[i], " ")))
      nargs++;
  }
  
  char ** args = parse_args(nargs, s);
  
  f = fork();
  
  if (!f){
    printf("Child executing\n");
    execvp(args[1], args);
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
  printf("%s \n",args[2]);
    return 0;

}
