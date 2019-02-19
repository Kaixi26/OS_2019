#include "readln.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void printlines (int fd, int nl){
    int i,rd=1;
    int bufSize = 1024;
    char *buf = calloc (bufSize, sizeof(char));
    for (i=0; i < nl; i++){
        rd = readln(fd, buf, bufSize);
        write (STDOUT_FILENO, buf, rd);
        write (STDOUT_FILENO, "\n", 1);
    }
}

int getArgument (char *arg){
    if (arg[0] == '-' && arg[1] == 'l' && arg[2] == '=')
        return atoi(arg+3);
    return 0;
}
int main (int argc, char **argv){
    int nl=5;
    int temp;
    int argi=1;
    char buf[1024];
    if ((temp = getArgument(argv[1]))){
        nl = temp;
        argi++;
    }
    while (argi < argc){
        
        write (STDOUT_FILENO, buf, sprintf (buf, "file %s:\n", argv[argi]));
        int fd = open (argv[argi], O_RDONLY);
        printlines (fd, nl);
        close(fd);
        argi++;
    }

	return 0;
}

