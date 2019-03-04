#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main (int argc, char **argv){
    int i;
    puts ("NAME\tSTATUS\tCOUNT");
    for (i=1; i<argc && fork(); i++)
        ;
    if (i != argc) {
        printf("%s\tINIT\t ---\n", argv[i]);
        int execAm = 0;
        int ret;
        int stat;
        do {
            if (!fork()){
                execl(argv[i], argv[i], NULL);
                _exit (0);
            }
            execAm++;
            wait (&stat);
            ret = WEXITSTATUS (stat);
        } while (ret != 0);
        printf("%s\tENDED\t%d\n", argv[i], execAm);
        _exit (0);
    }

    while (wait(NULL) != -1)
        ;
    puts ("All jobs ended!");
	return 0;
}

