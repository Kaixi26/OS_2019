#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char **argv){
    if(!fork())
        execl ("/bin/ls", "-l", NULL);
    puts("waiting for child");
    wait (NULL);
    puts("child finished");
	return 0;
}

