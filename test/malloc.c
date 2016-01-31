/*
** malloc for malloc
**
** Made by pirou_g in /home/pirou_g/piscine_tek2/malloc
** Login   <pirou_g@epitech.net>
**
** Started on     31/01/16 20:57
** Last update on 31/01/16 20:57
*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "malloc.h"

static t_alloc_data alloc_data = {NULL, NULL, NULL, NULL, 0};
static t_free_data  free_data = {NULL, NULL, {NULL}};

bool                init_alloc_data(void)
{
    size_t          padding;

    if ((alloc_data.start_heap = sbrk(0)) == (void*)-1)
        return (false);
    padding = sizeof(void*) - ((size_t)alloc_data.start_heap % sizeof(void*));
    if (padding > 0 && brk(alloc_data.start_heap + padding))
        return (false);
    else
        alloc_data.start_heap += padding;
    alloc_data.end_heap = alloc_data.start_heap;
    return (true);
}

bool                alloc_mem(size_t size)
{
    if ((alloc_data.start_heap == NULL && !init_alloc_data()) ||
        brk(alloc_data.end_heap + size) < 0)
        return (false);
    alloc_data.end_heap += size;
    alloc_data.unassigned_mem += size;
    return (true);
}

void                create_block(void *mem, size_t size)
{
    t_header*       block;

    if ((block = mem) == NULL)
        return;
    block->size = size;
    block->prev_address = NULL;
    block->prev_size = NULL;
    block->next_address = NULL;
    block->next_size = NULL;
}

void                update_list(t_header *block, t_header **start, t_header **end)
{
    if (block == NULL)
        return;
    if (start != NULL && *start == NULL)
        *start = block;
    if (end != NULL)
    {
        if (*end == NULL) {
            *end = block;
            block->prev_address = NULL;
        }
        else {
            (*end)->next_address = block;
            block->prev_address = *end;
            *end = block;
        }
    }
    block->next_address = NULL;
}

void*               malloc(size_t size)
{
    size_t          block_size;
    void*           block;

    size += sizeof(void*) - (size % sizeof(void*));
    block_size = size + sizeof(t_header);
    if (alloc_data.unassigned_mem < block_size &&
        !alloc_mem(block_size + BLOC_SIZE))
        return (NULL);
    block = alloc_data.end_heap - alloc_data.unassigned_mem;
    create_block(block, size);
    update_list(block, &(alloc_data.first_block), &(alloc_data.last_block));
    alloc_data.unassigned_mem -= block_size;
    return (block + sizeof(t_header));
}

void                free(void* ptr)
{
    (void)ptr;
}

void*               calloc(size_t n, size_t size)
{
    void*           dest;

    size *= n;
    if ((dest = malloc(size)) == NULL)
        return (NULL);
    return (memset(dest, 0, size));
}

void*               realloc(void* ptr, size_t size)
{
    t_header*       header;
    void*           dest;

    if (ptr == NULL)
        return (malloc(size));
    else if (size == 0)
    {
        free(ptr);
        return (NULL);
    }
    header = (ptr - sizeof(t_header));
    if (header->size >= size)
        return (ptr);
    if ((dest = malloc(size)) == NULL)
        return (NULL);
    memcpy(dest, ptr, header->size);
    free(ptr);
    return (dest);
}

void                show_alloc_mem(void)
{
    t_header*       csr;

    if ((csr = alloc_data.first_block) == NULL)
        return;
    fprintf(stdout, "===== Start of show_alloc_mem =====\n");
    while (csr != NULL)
    {
        fprintf(stdout, "Size of block : %ld\n", csr->size);
        fprintf(stdout, "Address of previous block in address : %p\n", csr->prev_address);
        fprintf(stdout, "Address of next block in address : %p\n", csr->next_address);
        fprintf(stdout, "*****\n");
        csr = csr->next_address;
    }
    fprintf(stdout, "===== End of show_alloc_mem =====\n");
}

void                show_free_mem(void)
{
    t_header*       csr;

    if (free_data.first_block == NULL)
        return;
    fprintf(stdout, "===== Start of show_free_mem =====\n");
    while (csr != NULL)
    {
        fprintf(stdout, "Size of block : %ld\n", csr->size);
        fprintf(stdout, "Address of previous block in address : %p\n", csr->prev_address);
        fprintf(stdout, "Address of next block in address : %p\n", csr->next_address);
        fprintf(stdout, "Address of previous block in size : %p\n", csr->prev_size);
        fprintf(stdout, "Address of next block in size : %p\n", csr->next_size);
        fprintf(stdout, "*****\n");
        csr = csr->next_address;
    }
    fprintf(stdout, "===== End of show_free_mem =====\n");
}