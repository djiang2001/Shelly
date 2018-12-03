# Shelly
by Dahong Jiang and Stefan Tan 

## Features:
* Forks and executes commands including cd and exit!
* Parses multiple commands on one line!
* Redirects using >, <!
* Implements simple pipes!
## Attempted:
The following did not end up working, but have been left in the code, commented out.
* Tried to catch signals such as SIGINT.
* Tried to handle multiple redirects.
## Bugs:

## Files & Function Headers:
*void printCurDir();
     Prints out the command line prompt for our shell
     Inputs:None
     Finds the current directory and prints it as the
     command prompt

*static void sighandler( int signo );
     Attempted this but was not successful

*void redirectOut(char ** args, int nargs);
     Redirects a function output to another file
     Input: The string array that contains the arguments
     	    and the number of arguments
     Output: None
     Forks a new child process and opens a new file with
     read or create status and dup2() it before executing

*void redirectIn(char ** args, int nargs);
     Redirects a function output into another file
     Input: The string array that contains the arguments
     	    and the number of arguments
     Output: None
     Forks a new child process and opens a new file with
     read status. The function dup2() is used on the file
     before reading the file output into the arguments
     for execution
     
*void redirectOutApp(char ** args, int nargs);
     Redirects a function output to another file
     Input: The string array that contains the arguments
     	    and the number of arguments
     Output: None
     Forks a new child process and opens a new file with
     read,create, or append status and dup2() it before
     executing

*int piper(char ** args);
    Pipes a command output to another command
    Input: Array of arguments
    Output: Returns 0 if successful
    Takes in an argument from one pipe and reads
    it into another file storing it

*void exec(char ** args);
    Creates a child process to execute a command
    Input: Number of arguments and argument array
    Output: None
    Takes in arguments that are parsed and executes it
    through a forked child process while the parent waits
    If the command is cd or exit, chdir is used with cd
    and exit(0) is used with exit