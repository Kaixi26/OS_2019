#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "system.c"

#define BUF_SIZE    1024

void print_prompt (){
    printf ("shit shell > ");
    fflush(stdin);
}

int main (int argc, char **argv){
    printf ("Full command path and arguments must be given ");
    printf ("i.e \"/bin/ls .\" to get current directory\n");
    char *buf = calloc (BUF_SIZE, sizeof(char));
    while (strncmp(buf, "exit", 4)){
        print_prompt ();
        if (!fgets (buf, BUF_SIZE, stdin)) break;
        int len = strlen(buf)-1;
        buf[len] = 0;   /* Remove \r */
        if (buf[len-1] == '&'){
            buf[len-1] = 0;
            char *tmp = strdup (buf);
            if (fork())
                continue;
            mysystem (tmp);
            free (tmp);
            _exit (0);
        }
        mysystem (buf);
    }
    
	return 0;
}

