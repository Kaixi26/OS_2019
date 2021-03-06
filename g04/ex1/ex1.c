#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (int argc, char **argv){
    int fd0 = open ("stdin.txt" , O_CREAT | O_RDONLY, 0666);
    int fd1 = open ("stdout.txt", O_CREAT | O_WRONLY, 0666);
    int fd2 = open ("stderr.txt", O_CREAT | O_WRONLY, 0666);
    dup2 (fd0, STDIN_FILENO);
    dup2 (fd1, STDOUT_FILENO);
    dup2 (fd2, STDERR_FILENO);

    int rd;
    char buf[10];
    while ((rd = read (STDIN_FILENO, buf, 10))){
        write (STDOUT_FILENO, buf, rd);
        write (STDERR_FILENO, buf, rd);
    }
    exit(0);

    close (fd0);
    close (fd1);
    close (fd2);

	return 0;
}
