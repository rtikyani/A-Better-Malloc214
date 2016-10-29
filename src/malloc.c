#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "malloc.h"

/*
 * The memory heap.
 */
static char memory_heap[HEAP_SIZE];

/*
 * The root memory block.
 */
static block_t *root;

/*
 * A function which detects memory that hasn't been freed before exiting.
 */
static void check_for_memory_leaks() {
    block_t *current_block = root;

    while (current_block->next != NULL) {
        if (!current_block->is_free) {
            fprintf(stderr, "Error: Found memory leak. (%s, line %d)\n", current_block->file, current_block->line);
        }

        current_block = current_block->next;
    }

}

/*
 * Initializes the heap and adds a shutdown hook for detecting memory leaks.
 */
static void initialize() {
    size_t block_size = HEAP_SIZE - sizeof(block_t);
    root = create_block(memory_heap, NULL, block_size, true);
    atexit(&check_for_memory_leaks);
}

/*
 * A function used to defragment the memory heap.
 */
static void defragment() {
    block_t *current = root;

    while (current->next != NULL) {

        if (current->is_free && current->next->is_free) {
            current->size = current->size + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }

    }

}

/*
 * Finds the allocated block for a given block.
 */
static void *find_block(block_t *block) {
    return block + sizeof(block_t);
}

/*
 * Gets a block, given the allocated block.
 */
static block_t *get_block(void *block) {
    block_t *current = root;

    while (current != NULL) {
        void *current_block = find_block(current);

        if (current_block == block) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

/*
 * Allocates a block.
 */
void *_malloc(size_t size, char *file, int line) {
    if (root == NULL) {
        initialize();
    }

    block_t *current = root;

    while (current != NULL) {
        if (current->is_free && current->size >= size) {
            void *block_address = ((char *) current) + sizeof(block_t) + size;
            size_t block_size = current->size - size;
            block_t *block = create_block(block_address, current->next, block_size, true);

            current->file = file;
            current->line = line;
            current->size = size;
            current->is_free = false;
            current->next = block;
            return find_block(current);
        } else if (current->next == NULL) {
            fprintf(stderr, "Error: Not enough memory. (%s, line %d)\n", file, line);
        }
        current = current->next;
    }

    return NULL;
}

/*
 * Frees a block of data from memory, given the pointer to the data.
 */
void _free(void *address, char *file, int line) {
    block_t *block = get_block(address);

    if (block && !block->is_free) {
        block->is_free = true;
        defragment();
    } else {
        fprintf(stderr, "Error: Cannot free memory which wasn't allocated by malloc. (%s, line %d)\n", file, line);
    }
}