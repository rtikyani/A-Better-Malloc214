#include <string.h>
#include <stdbool.h>
#include "block.h"

/*
 * Creates a block.
 */
block_t *create_block(void *location, block_t *next, size_t size, bool free) {
    block_t *block = (block_t *) location;
    block->next = next;
    block->size = size;
    block->is_free = free;
    block->next = NULL;
    block->file = NULL;
    block->line = -1;
    return block;
}
