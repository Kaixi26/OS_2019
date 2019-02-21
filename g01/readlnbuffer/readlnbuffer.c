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

ssize_t readln_buffer (Buffer_t *buf_t, void *buf, size_t nbyte){
    size_t i = 0;
    size_t last_i = 0;
    size_t ini_cursor = buf_t->cursor;
    nbyte--;            /* save space for NUL */
    while (i < nbyte){
        if (end_reached_buffer (buf_t)){
            memcpy ((char*)buf+last_i, buf_t->buf + ini_cursor, i - last_i);
            last_i = i;
            if (refill_buffer (buf_t) <= 0)
                break;
            ini_cursor = 0;
        }
        i++;
        if (buf_t->buf[buf_t->cursor++] == '\n'){
            break;
        }
    }
//    printf ("%d %d %d\n", i, last_i, buf_t->cursor);
    memcpy ((char*)buf+last_i, buf_t->buf + ini_cursor, i - last_i);
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
