#include "readln.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main (int argc, char **argv){
    size_t bufSize = 100;
    char *buf = calloc (bufSize, sizeof(char));
    int fd = open (argv[1], O_RDONLY);
    ssize_t rd;
    for (int i=0; i < 5; i++){
        rd = readln(fd, buf, bufSize);
        write (STDOUT_FILENO, buf, rd);
        write (STDOUT_FILENO, "\n", 1);
    }
    close (fd);
	return 0;
}

