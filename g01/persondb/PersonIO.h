#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./lib/Person.h"
#include "./lib/readln.h"

/*
 * Reads a person from file descriptor, must be in the format "<int age><char *name>\n"
 * fd represents the file descriptor (must have read flag)
 * maxAlloc is the total size to allocate for the buffer
 * Returns a pointer to an allocated function with an allocated name, the size allocated for the name will be the length of the string
 * If it cannot read until \n it will return NULL and try to move the file descriptor to the place before the call
*/

Person *readPersonLn (int fd, size_t maxAlloc);

int writePerson (int fd, Person *p);
int writePerson_ (int fd, char *str, int age);

int seekPerson (int fd, Person *p);
