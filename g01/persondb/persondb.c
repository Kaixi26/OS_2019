#include "PersonIO.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int addPerson (int fd, Person *p){
    lseek(fd, 0, SEEK_END);
    writePerson (fd, p);
    return 0;
}

int addPerson_ (int fd, char *name, int age){
    lseek(fd, 0, SEEK_END);
    writePerson_ (fd, name, age);
    return 0;
}

int main (int argc, char **argv){
    if (argc < 4){
        puts ("bad input");
        return 1;
    }
    int fd = open ("./data/database", O_CREAT | O_RDWR, 0666);
    if (!strcmp(argv[1], "-i")){
        Person p = new_person (argv[2], atoi(argv[3]));
        addPerson (fd, &p);

    }
    else if (!strcmp(argv[1], "-m")){
        for(int i=2; i < argc; i+=2)
            addPerson_ (fd, argv[i], atoi(argv[i+1]));
    }
    else if (!strcmp(argv[1], "-u")){
        Person p = new_person (argv[2], 0);
        printf ("%d\n", seekPerson(fd, &p));
    }
    close (fd);
	return 0;
}

