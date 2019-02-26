#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char **argv){
    printf (
        "process id:%d\nparent process id:%d\n"
      , getpid ()
      , getppid ()
      );
	return 0;
}

