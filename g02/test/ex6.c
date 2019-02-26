#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

#define MAT_DIM 1024
#define THREADS 10


int main (int argc, char **argv){

    int is_child; 
    for (int i = 0; i < THREADS; i++){
        is_child = !fork ();
        if (is_child){
            puts ("hi");
            _exit (0);
        }
    }

    for (int i = THREADS;i > 0; i--){
        wait (NULL);
    }
	return 0;
}

