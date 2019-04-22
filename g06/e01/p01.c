#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

int main (){
    mkfifo ("fifo", 0622);
    while(1)
        sleep (1);
    return 0;
}
