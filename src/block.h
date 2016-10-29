#ifndef _ENTRY_H_
#define _ENTRY_H_

#include <stdbool.h>

/*
 * A memory block.
 */
typedef struct block {
    struct block *next;
    size_t size;
    char *file;
    int line;
    bool is_free;
} block_t;

/*
 * Creates a block.
 */
block_t *create_block(void *, block_t *, size_t, bool);

#endif