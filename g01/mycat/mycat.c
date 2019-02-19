#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/*
 * Reads from stdin one byte at a time until it reaches EOF
 * fd === file descriptor
 * buf === buffer to store the read contents
 * size === size of the buffer
 * chunckSize === bytes read with each read() call
 * If chunckSize is equal to 0 then contents of fd will be consumed in one read()
*/

int readfd (int fd, char *buf, size_t size, int chunckSize) {
    if (!chunckSize)
        chunckSize = size;
    size--;
    int i;
    int rd=1;

    for (i = 0; rd && i < size; i+=rd)
        rd = read (fd, buf+i, chunckSize);
    buf[i+1] = 0;
    return i;
}

void _usage (char *proc) {
    printf ("Usage : %s <chunck size> <(optional) files>", proc);
}

int _getChunck (char *s) {
    int temp = atoi(s);
    if (temp == 0 && !(s[0] == '0' && !s[1]))
        temp = -1;
    return temp;
}

int main (int argc, char **argv){
    size_t bufSize = 1024 * 1024 * 20;
    char *buf = malloc (bufSize * sizeof(char));
    int chunckSize;
    int read;
    if (argc < 2){
        _usage(argv[0]);
        return 1;
    }
    if ((chunckSize = _getChunck (argv[1])) < 0)
        return 2;
    if ( argc == 2){
        while ((read = readfd (STDOUT_FILENO, buf, bufSize, chunckSize)))
            write (STDOUT_FILENO, buf, read);
        return 0;
    }
    for (int i=2; i < argc; i++){
        int fd = open (argv[i], O_RDONLY);
        while ((read = readfd (fd, buf, bufSize, chunckSize)))
            write (STDOUT_FILENO, buf, read);
        close (fd);
    }
    free (buf);
	return 0;
}

