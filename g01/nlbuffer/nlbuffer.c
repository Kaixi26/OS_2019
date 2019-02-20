#include "readlnbuffer.h"
#include <stdio.h>

int main (int argc, char **argv){
    size_t bufSize = 1024;
    char *buf = calloc (bufSize, sizeof(char));
    Buffer_t *buf_t = create_buffer (0, 1024);

    int count = 1;
    while (readln_buffer (buf_t, buf, bufSize) > 1){
        printf ("\t%d %s", count++, buf);
    }

    close_buffer (buf_t);
	return 0;
}

