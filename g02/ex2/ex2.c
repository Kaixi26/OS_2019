#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char **argv){
    fork ();
    printf ("Par:%d\tCur:%d\n", getppid(), getpid());
	return 0;
}

