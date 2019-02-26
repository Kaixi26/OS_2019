#include <unistd.h>

/*
 * Reads the file descriptor until it finds a new line or until it fills buf with nbyte
 * IF IT WAS NOT ABLE TO READ UNTIL \n WILL RETURN NUMBER OF BYTES READ*-1
*/
ssize_t readln (int fd, void *buf, size_t nbyte);
