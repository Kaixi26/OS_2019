#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>

int main (){
    int fd = open ("fifo", O_WRONLY);
    write (STDOUT_FILENO, "Opened!\n", strlen ("Opened!\n"));
    int rd;
    char buffer[1024];
    if (fd == -1)
        return -1;
    while ((rd = read (STDIN_FILENO, buffer, 1024)))
        write (fd, buffer, rd);
    close (fd);
    return 0;
}
