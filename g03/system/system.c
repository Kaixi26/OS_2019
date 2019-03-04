#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <string.h>

int getargc (const char *command){
    int argc = 1;
    int prev = 0;
    for (int i=0; command[i]; i++){
        if (!prev && (prev = isspace(command[i])))
            argc++;
    }
    return (argc+1);
}

char **partition (char *command){
    int argc = getargc (command);
    char **tmp = calloc (argc + 1, sizeof(char*));
    int i=0, j=0;
    tmp[j++] = &(command[i]);
    for (int i=0; command[i]; i++){
        if (isspace(command[i])){
            command[i] = 0;
            if (!isspace(command[i+1]))
                tmp[j++] = &(command[i+1]);
        }
    }
        
    return tmp;
}

int system (const char *command){
    pid_t childpid;
    char *tmp = strdup (command);
    if (!(childpid = fork())){
        char **part = partition (tmp);
        execv (part[0], &(part[1]));
        _exit (1);
    }
    pid_t stat;
    waitpid (childpid, &stat, 0);
    if (tmp) free (tmp);
    return 0;
}


int main (int argc, char **argv){
    system ("/bin/ls -l -a");
	return 0;
}

