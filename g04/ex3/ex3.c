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

    if (fork()){
        execl ("/bin/wc", "/bin/wc", NULL);
        exit(0);
    }

    wait (NULL);
    close (fd0);
    close (fd1);
    close (fd2);

	return 0;
}
