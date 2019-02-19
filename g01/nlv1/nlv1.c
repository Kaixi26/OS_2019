#include "readln.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv){
    int n;
    size_t bufSize = 1024;
    char *buf = calloc (bufSize, sizeof(char));
    for (n=1; readln (STDIN_FILENO, buf, bufSize); n++){
        printf ("\t%d  %s\n", n, buf);
    }
	return 0;
}

