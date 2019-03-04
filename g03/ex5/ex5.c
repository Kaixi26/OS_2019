#include <unistd.h>

int main (int argc, char **argv){
    for (int i=1; i<argc; i++){
        if (!fork())
            execl (argv[i], argv[i], NULL);
    }
	return 0;
}

