#include "readln.h"
#include <stdio.h>

ssize_t readln (int fd, void *buf, size_t nbyte) {
    nbyte--;
    char *cbuf = (char*) buf;
    int i;
    int rd=1;
    off_t foundnl = 0;

    rd = read (fd, cbuf, nbyte);
    for (i = 0; i < rd; i++)
        if (cbuf[i] == '\n'){
            foundnl = 1;
            break;
        }
    cbuf[i] = 0;
    lseek (fd, (i - rd) + foundnl, SEEK_CUR);

    return (foundnl == 1 ? i : -i);
}
