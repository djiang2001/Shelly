void printCurDir();

static void sighandler( int signo );

void redirectOut(char ** args, int nargs);

void redirectIn(char ** args, int nargs);

void redirectOutApp(char ** args, int nargs);

int piper(char ** args);

void exec(char ** args);
