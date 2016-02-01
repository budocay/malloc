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

void                list_push_back(t_header *block, t_header **start, t_header **end)
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

void                insert_block_in_alloc_list(t_header* block)
{
    t_header*       csr;

    if (block == NULL)
        return;
    if ((csr = alloc_data.first_block) == NULL)
    {
        alloc_data.first_block = block;
        alloc_data.last_block = block;
        csr->next_address = NULL;
        csr->prev_address = NULL;
        return;
    }
    while (csr->next_address != NULL && csr < block)
        csr = csr->next_address;
    if (csr < block)
    {
        block->next_address = csr->next_address;
        block->prev_address = csr;
        csr->next_address = block;
    }
    else
    {
        block->next_address = csr;
        block->prev_address = csr->prev_address;
        csr->prev_address = block;
    }
}

t_header*           get_best_fit(size_t size)
{
    size_t          idx;
    t_header*       csr;

    if (free_data.first_block == NULL || (idx = GET_FREE_IDX(size)) == BIG_IDX)
        return (NULL);
    while (idx < (BLOCK_SIZE - sizeof(t_header)) &&
           idx <= (GET_FREE_IDX(size) + 5))
    {
        if ((csr = free_data.blocks[idx]) != NULL)
        {
            if (csr == free_data.first_block)
                free_data.first_block = free_data.first_block->next_address;
            if (csr == free_data.last_block)
                free_data.last_block = free_data.last_block->prev_address;
            if (csr->next_address != NULL)
                csr->next_address->prev_address = csr->prev_address;
            if (csr->prev_address != NULL)
                csr->prev_address->next_address = csr->next_address;
            free_data.blocks[idx] = csr->next_size;
            if (csr->next_size != NULL)
                csr->next_size->prev_size = csr->prev_size;
            if (csr->prev_size != NULL)
                csr->prev_size->next_size = csr->next_size;
            csr->next_size = NULL;
            csr->prev_size = NULL;
            insert_block_in_alloc_list(csr);
            return (csr);
        }
        ++idx;
    }
    return (NULL);
}

void*               malloc(size_t size)
{
    size_t          block_size;
    void*           block;
    void*           fit_block;

    size += sizeof(void*) - (size % sizeof(void*));
    block_size = size + sizeof(t_header);
    if ((fit_block = get_best_fit(size)) != NULL)
        return (fit_block + sizeof(t_header));
    if (alloc_data.unassigned_mem < block_size &&
        !alloc_mem(block_size + (BLOCK_SIZE - (block_size % BLOCK_SIZE))))
        return (NULL);
    block = alloc_data.end_heap - alloc_data.unassigned_mem;
    create_block(block, size);
    list_push_back(block, &(alloc_data.first_block), &(alloc_data.last_block));
    alloc_data.unassigned_mem -= block_size;
    return (block + sizeof(t_header));
}

void                put_block_in_size_free_list(t_header *header)
{
    size_t          idx;
    t_header*       csr;

    if (header == NULL)
        return;
    idx = GET_FREE_IDX(header->size);
    csr = free_data.blocks[idx];
    if (idx < (BLOCK_SIZE / sizeof(void*)))
    {
        header->next_size = csr;
        header->prev_size = NULL;
        if (csr != NULL)
            csr->prev_size = header;
        free_data.blocks[idx] = header;
    }
    else
    {
        if (csr == NULL)
        {
            free_data.blocks[idx] = header;
            return;
        }
        while (csr->next_size != NULL && csr->size <= header->size)
            csr = csr->next_size;
        header->next_size = csr->next_size;
        header->prev_size = csr;
        csr->next_size = header;
    }
}

void                put_block_in_address_free_list(t_header *header)
{
    if (header == NULL)
        return;
    if (header->prev_address != NULL)
        header->prev_address->next_address = header->next_address;
    if (header->next_address != NULL)
        header->next_address->prev_address = header->prev_address;
    header->next_address = NULL;
    header->prev_address = free_data.last_block;
    if (free_data.first_block == NULL)
        free_data.first_block = header;
    else
        free_data.last_block->next_address = header;
    free_data.last_block = header;
}

void                free(void* ptr)
{
    t_header*       header;

    if (ptr == NULL)
        return;
    header = ptr - sizeof(t_header);
    put_block_in_size_free_list(header);
    put_block_in_address_free_list(header);
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

    fprintf(stdout, "===== Start of show_free_mem =====\n");
    if ((csr = free_data.first_block) == NULL)
        return;
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

void                show_free_lists(void)
{
    size_t          idx;
    t_header*       csr;

    idx = 0;
    fprintf(stdout, "===== Start of show_free_lists =====\n");
    while (idx <= BIG_IDX)
    {
        if ((csr = free_data.blocks[idx]) != NULL)
        {
            fprintf(stdout, "Idx = %ld\n", idx);
            while (csr != NULL)
            {
                fprintf(stdout, "Size of block : %ld\n", csr->size);
                fprintf(stdout, "Address of previous block in address : %p\n", csr->prev_address);
                fprintf(stdout, "Address of next block in address : %p\n", csr->next_address);
                fprintf(stdout, "Address of previous block in size : %p\n", csr->prev_size);
                fprintf(stdout, "Address of next block in size : %p\n", csr->next_size);
                fprintf(stdout, "*****\n");
                csr = csr->next_size;
            }
            fprintf(stdout, "/////\n");
        }
        idx++;
    }
    fprintf(stdout, "===== End of show_free_lists =====\n");
}