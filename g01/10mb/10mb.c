#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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

void _usage (char *proc) {
    printf ("Usage : %s <chunck size> <output filename>\n", proc);
}

int _getChunck (char *s) {
    int temp = atoi(s);
    if (temp == 0 && !(s[0] == '0' && !s[1]))
        temp = -1;
    return temp;
}

int main (int argc, char **argv){
    int chunck;
    if (argc < 3){
        _usage(argv[0]);
        return 1;
    }
    else if ((chunck = _getChunck(argv[1])) < 0)
        return 2;

    int fd = open (argv[2], O_CREAT | O_WRONLY, 0666);
    if (fd < 0){
        puts ("An error occured while opening the file.");
        return 3;
    }
    writeTrash (fd, 1024 * 1024 * 10, chunck);
    close (fd);

	return 0;
}

