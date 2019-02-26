#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char **argv){
    int i;
    int s;
    for (i=1; i<11; i++){
        if(!fork ()){
            printf ("Hi, I am process %d, my parent is %d\n", getpid(), getppid());
            _exit (i);
        }
        else {
            wait (&s);
            printf ("Exited : %d\n", WEXITSTATUS(s));
        }
    }

	return 0;
}

