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

void exec(char ** args){
  int f, status;

  if (!strcmp(args[0], "cd")){
    chdir(args[1]);
  }
  if (!strcmp(args[0], "exit")){
    exit(0);
  }
  f = fork(); 
  if (!f){
    execvp(args[0], args);
  }
  else {
    wait(&status);
    return;
  }
} 
  

int main(){
  int status, f;
  
  while(1){
    // printCurDir();
    char *s = malloc(100 * sizeof(char));
    scanf("%[^\n]s", s);
    
    char ** args = parse_args(s);
    exec(args);
  }
  return 0;

}
