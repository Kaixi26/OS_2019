#include "PersonIO.h"
#include <stdio.h>

Person *readPersonLn (int fd, size_t maxAlloc){
    Person *temp = malloc (sizeof(Person));
    char *buf = malloc (maxAlloc * sizeof(char));
    ssize_t ird = read (fd, (char*)&(temp->age), sizeof(int));
    if (ird <=0)
        return NULL;
    ssize_t srd = readln(fd, buf, maxAlloc);
    if (srd <= 0){
        lseek (fd, srd - ird, SEEK_CUR);
        return NULL;
    }

    temp->name = strdup(buf);
    free (buf);
    return temp;
}

int writePerson (int fd, Person *p){
    write (fd, (char*)&(p->age), sizeof(int));
    write (fd, p->name, strlen(p->name));
    write (fd, "\n", 1);
    return 0;
}

int writePerson_ (int fd, char *name, int age){
    write (fd, (char*)&age, sizeof(int));
    write (fd, name, strlen(name));
    write (fd, "\n", 1);
    return 0;
}

int seekPerson (int fd, Person *p){
    size_t bufSize = strlen(p->name) + 1024;
    char *buf = calloc(bufSize, sizeof(char));
    int eq=0;
    int rd;

    while (!eq && (rd = readln(fd, buf, bufSize))){
        if (rd < 0)
            while ((rd = readln(fd, buf, bufSize) < 0)){
            }
        eq = !strcmp (p->name, buf + sizeof(int));
        puts(buf);
    }
    if (eq)
        lseek (fd, -rd, SEEK_CUR);
    return eq;
}
