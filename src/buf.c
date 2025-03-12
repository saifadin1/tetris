#include "../include/buf.h"
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>


void append_buf(buf_t *buf, const char *c, int len) {
    char *new = realloc(buf->buf, buf->len + len);
    if (new == NULL)
        return;
    memcpy(&new[buf->len], c, len);
    buf->buf = new;
    buf->len += len;
}

void free_buf(buf_t *buf) {
    free(buf->buf);
}