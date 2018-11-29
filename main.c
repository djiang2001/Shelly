#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void printCurDir() { 
    char cwd[256]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\ncwd: %s$ ", cwd); 
} 

char ** parse_args( char * line ) {
  char ** a = malloc(100 * sizeof(char *));
  int i = 0;
  while(line) {
    a[i] = strsep(&line, " ");
    i++;
  }
  return a;
}

int exec(char ** args){
  int f, status;

  if (!strcmp(args[0], "cd")){
    chdir(args[1]);
  }
  /* DOESNT WORK
  if (!strcmp(args[0], "exit")){
    return 0;
  }
  */
  f = fork();
  
  if (!f){
    execvp(args[0], args);
  }
  else {
    wait(&status);
    return 0;
  }
} 
  

int main(){
  int status, f;
  
  while(1){
    //printCurDir(); DOESNT WORK IT KEEPS PRINTING THIS
    char *s = malloc(100 * sizeof(char));
    scanf("%[^\n]s", s);
    
    char ** args = parse_args(s);
    exec(args);
    /* 
       f = fork();
    
       if (!f){
       // printf("Child executing\n");
       execvp(args[0], args);
       return 0;
       //printf("Error executing\n");
       }
       else {
       wait(&status);
       }*/
  }
  /*
    else if(f > 0){

    if((cpid = wait(&status)) < 0){
    printf("Waiting");
    exit(1);
    }
    
    printf("Parent: Complete\n");
    }else{
    printf("Fork failed\n");
    exit(1);
    }*/
  return 0;

}
