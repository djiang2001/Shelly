#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "main.h"

void printCurDir() { 
  char cwd[256]; 
  getcwd(cwd, sizeof(cwd)); 
  printf("\ncwd: %s$ ", cwd); 
} 

/*char ** parse_args( char * line ) {
  char ** a = malloc(100 * sizeof(char *));
  int i = 0;
  while(line) {
  a[i] = strsep(&line, " ");
  i++;
  }
  return a;
  }
*/

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
  }
} 
  

int main(){
  char line[50];
  printCurDir();
  while(fgets(line,50, stdin)){
    line[strlen(line)-1] = '\0';
    char *args[50];
    
    char * token;
    int numcmd = 1;
    char ** cmds = malloc(100 * sizeof(char *));
    token = strtok(line, ";");
    while(token) {
      cmds[numcmd-1] = token;
      token = strtok(NULL, ";");
      numcmd++;
    }

    int i = 0;
    while(numcmd > 1){
      int argcount = 0;
      char* tok = strtok(cmds[i], " ");
    
      while(tok){
	args[argcount] = tok;
	argcount++;
	tok = strtok(NULL," ");
      }
      args[argcount] = NULL;
      if(argcount > 0){
	exec(args);
      }
      i++;
      numcmd--;
    }
    printCurDir();
  }
  return 0;
}
