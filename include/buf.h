#pragma once

typedef struct {
    char *buf;
    int len;
} buf_t;

void append_buf(buf_t *buf, const char *c, int len);
void free_buf(buf_t *buf);