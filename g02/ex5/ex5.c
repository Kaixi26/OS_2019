#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char **argv){
    int i;
    printf("PID\t\tCPID\tIND\tIS_EXIT\n");
    for (i = 0; i < 10; i++){
        pid_t ch;
        if (!(ch = fork())){    /* Caso seja o processo filho */
            continue;
        }
        else {
            printf ("%d\t%d\t%d\t%d\n", getpid (), ch, i, 0);
            wait (NULL);
            printf ("%d\t%d\t%d\t%d\n", getpid (), ch, i, 1);
            _exit (0);
        }

    }
	return 0;
}

