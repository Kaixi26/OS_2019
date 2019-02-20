#include "readlnbuffer.h"

Buffer_t *create_buffer (int fd, size_t size){
    Buffer_t *buffer = calloc (sizeof(Buffer_t), 1);
    if (!buffer)
        return NULL;
    buffer -> buf = calloc (size, sizeof(char));
    if (!buffer->buf){
        free (buffer);
        return NULL;
    }
    buffer -> buf_size = size;
    buffer -> cur_buf_size = 0;
    buffer -> cursor = 0;
    buffer -> fd = fd;
    
    return buffer;
}

ssize_t refill_buffer (Buffer_t *buffer){
    ssize_t read_bytes = read (buffer->fd, buffer->buf, buffer->buf_size);
    buffer->cur_buf_size = read_bytes;
    buffer->cursor = 0;
    return read_bytes;
}

int end_reached_buffer (Buffer_t *buffer){
    return buffer->cursor >= buffer->cur_buf_size;
}

ssize_t readln_buffer (Buffer_t *buffer, void *buf, size_t nbyte){
    ssize_t i = 0;
    size_t max_i = nbyte - 1;
    while (i < max_i){
        if (end_reached_buffer (buffer))
            if (refill_buffer (buffer) <= 0)
                break;
        ((char*)buf)[i] = buffer->buf[buffer->cursor++];
        if (((char*)buf)[i++] == '\n')
            break;
    }
    ((char*)buf)[i] = 0;
    return i;
}

int destroy_buffer (Buffer_t *buffer){
    int fd = buffer->fd;
    free (buffer->buf);
    free (buffer);
    return fd;
}

void close_buffer (Buffer_t *buffer){
    int fd = destroy_buffer (buffer);
    close (fd);
}
