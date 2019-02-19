#include <unistd.h>

/*
 * Reads the file descriptor until it finds a new line or until it fills buf with nbyte
*/
ssize_t readln (int fd, void *buf, size_t nbyte);
