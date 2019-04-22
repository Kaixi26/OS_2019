#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>

int main (int argc, char** argv){
    if (argc != 2)
        return -1;
    int fifo = open ("fifo", O_WRONLY);
    write (fifo, argv[1], strlen(argv[1]));
    return 0;
}
