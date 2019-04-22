#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

int read_pipe (int* fd, char* path, void* buf, int bufsize){
    int rd = read (*fd, buf, bufsize);
    if (rd <= 0){
        close (*fd);
        *fd = open (path, O_RDONLY, 0666);
        rd = read (*fd, buf, bufsize);
    }
    return rd;
}

int main (){
    int log = open ("log", O_CREAT | O_WRONLY | O_APPEND, 0666);
    mkfifo ("fifo", 0666);
    int fifo = open ("fifo", O_RDONLY);
    char buf[1024];
    while (1){
        int rd = read_pipe (&fifo, "fifo", buf, 1024);
        write (log, buf, rd);
        write (log, "\n", 1);
    }
    close (fifo);
    close (log);
    return 0;
}
