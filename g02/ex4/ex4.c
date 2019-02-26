#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char **argv){
    int i;
    for (i=0; i<10; i++){
        if(!fork ()) break;    /* Sair do loop caso não seja o pai */
    }

    if (i < 10){
        printf ("Hi, I am process %d, my parent is %d\n", getpid(), getppid());
        _exit (i+1);
    }
    else {
        int s;
        for (int active_proc=10; active_proc > 0; active_proc--){
            wait (&s);
            printf ("Already exited : %d\n", WEXITSTATUS(s));
        }
    }
	return 0;
}

