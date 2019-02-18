#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * Reads from stdin one byte at a time until it reaches EOF
 * buf === buffer to store the read contents
 * size === size of the buffer
*/

int readStdin (char *buf, size_t size) {
    size--;
    int i;
    int rd=1;

    for (i = 0; rd && i < size; i+=rd)
        rd = read (STDIN_FILENO, buf+i, 1);
    buf[i+1] = 0;
    return i;
}

int main (int argc, char **argv){
    size_t bufSize = 1000;
    char *buf = malloc (bufSize * sizeof(char));
    int read;
    while ((read = readStdin (buf, bufSize)))
        write (STDOUT_FILENO, buf, read);
    free (buf);
	return 0;
}

