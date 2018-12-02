#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#include "main.h"

void printCurDir() { 
  char cwd[256]; 
  getcwd(cwd, sizeof(cwd)); 
  printf("\ncwd: %s$ ", cwd); 
}

/*
static void sighandler( int signo ) {
  if (signo == SIGINT) {
    printCurDir();
  }
}
*/

void redirectOut(char ** args, int nargs){
  int f, status;
  f = fork(); 
  if (!f){
    int fd = open(args[nargs-1], O_WRONLY | O_CREAT, 0777);
    dup2(fd, 1);
    args[nargs-2] = NULL;
    execvp(args[0], args);
  }
  else {
    wait(&status);
  }
}

void redirectIn(char ** args, int nargs){
  int f, status;
  f = fork(); 
  if (!f){
    int fd = open(args[nargs-1], O_RDONLY);
    char s[1024];
    char cur[256];
    dup2(fd, 0);
    while( fgets(cur, 256, stdin))
      strcat(s, cur);
    args[nargs - 2] = s;
    args[nargs - 1] = NULL;
    execvp(args[0], args);
  }
  else {
    wait(&status);
  }
}

void redirectOutApp(char ** args, int nargs){
  int f, status;
  f = fork(); 
  if (!f){
    int fd = open(args[nargs-1], O_WRONLY | O_CREAT | O_APPEND, 0777);
    dup2(fd, 1);
    args[nargs-2] = NULL;
    execvp(args[0], args);
  }
  else {
    wait(&status);
  }
}

int piper(char ** args){
  char readbuf[100];
  FILE *pipein, *pipeout;

  pipein = popen(args[0], "r");
  pipeout = popen(args[2], "w");
    
  while (fgets(readbuf, 100, pipein))
    fputs(readbuf, pipeout);
  pclose(pipein);
  pclose(pipeout);
  return 0;
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
  }
} 

int main(){
  //signal(SIGINT, sighandler);
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
      if (! strcmp(args[argcount-2], ">" ) ){
	redirectOut(args, argcount);
      }
      if (! strcmp(args[argcount-2], "<") ){
	redirectIn(args, argcount);
      }
      if (! strcmp(args[argcount-2], ">>" ) ){
	redirectOutApp(args, argcount);
      }
      if (! strcmp(args[argcount-2], "|" ) ){
	piper(args);
      }
      else if(argcount > 0){
	exec(args);
      }
      i++;
      numcmd--;
    }
    printCurDir();
  }
  return 0;
}
