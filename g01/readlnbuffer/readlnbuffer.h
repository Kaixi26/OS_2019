#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct buffer_t {
    /* The buffer itself */
    char   *buf;
    /* Amount of bytes allocated to the buffer */
    size_t buf_size;
    /* Current filled space in buffer */
    size_t cur_buf_size;
    /* First unread index in the buffer */
    size_t cursor;
    /* File descriptor from which to read */
    int    fd;
} Buffer_t;

/*  Creates a buffer
    Returns
        the buffer if sucessful
        NULL if there was an error allocating memory
*/
Buffer_t *create_buffer (int filedes, size_t size);

/*  Deallocates a buffer and returns the used file descriptor */
int destroy_buffer      (struct buffer_t *buffer);

/*  Deallocates a buffer and closes it's file descriptor */
void close_buffer       (struct buffer_t *buffer);

ssize_t readln_buffer   (struct buffer_t *buffer, void *buf, size_t nbyte);
