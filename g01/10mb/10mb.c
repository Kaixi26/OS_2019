#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * writes 'a's to a file
 * fd === file descriptor
 * size === amount of bytes to write
 * chunck === amount of bytes for each write() call
 * if chunck is equal to 0, all the bytes will be written with one write() call
*/

int writeTrash (int fd, size_t size, size_t chunck){
    if (!chunck)
        chunck = size;
    char *buf = malloc (chunck * sizeof(char));
    size_t i;
    for (i=0; i < chunck; i++)
        buf[i] = 'a';
    for (i=0; i < size - chunck; i+=chunck)
        write (fd, buf, chunck);
    write (fd, buf, size - i);
    free (buf);
    return 0;
}

void _usage (char **argv) {
    printf ("Usage : %s <chunck size> <output filename>\n", argv[0]);
}

int main (int argc, char **argv){
    int fd = open ("10mb.dat", O_CREAT | O_WRONLY, 0666);
    writeTrash (fd, 1024 * 1024 * 10, 0);
    close (fd);
	return 0;
}

