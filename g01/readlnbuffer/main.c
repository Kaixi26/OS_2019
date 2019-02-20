#include "readlnbuffer.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char **argv){
    int bufSize = 1024;
    char *buffer = calloc (bufSize, sizeof(char));
    int fp = open ("testfile.txt", O_RDONLY);
    Buffer_t *buf_t = create_buffer (fp, 4);
    for (int i=0; i<100; i++){
        readln_buffer (buf_t, buffer, bufSize);
        printf ("%s", buffer);
    }
    close_buffer (buf_t);
	return 0;
}

