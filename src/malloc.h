#ifndef _MALLOC_H_
#define _MALLOC_H_

/*
 * Our 'malloc' and 'is_free' macros.
 */
#define malloc(size) _malloc(size, __FILE__, __LINE__)
#define free(address) _free(address, __FILE__, __LINE__)

/*
 * The size of the memory_heap.
 */
#define HEAP_SIZE 5000

/*
 * Allocates a block of data, given the size.
 */
void *_malloc(size_t, char *, int);

/*
 * Frees a block of data from memory, given the pointer to the data.
 */
void _free(void *, char *, int);

#endif