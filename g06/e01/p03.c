#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>

int main (){
    int fd = open ("fifo", O_RDONLY);
    write (STDOUT_FILENO, "Opened!\n", strlen ("Opened!\n"));
    int rd;
    char buffer[1024] = {0};
    if (fd == -1)
        return -1;
    while ((rd = read (fd, buffer, 1024)))
        write (STDOUT_FILENO, buffer, rd);
    close (fd);
    return 0;
}
