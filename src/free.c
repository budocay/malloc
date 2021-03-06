/*
** free.c for free in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Fri Feb 12 11:27:25 2016 lina_a
** Last update Fri Feb 12 11:27:25 2016 lina_a
*/

#include <stddef.h>
#include <unistd.h>
#include "malloc.h"

void            reset_heap(void)
{
    t_alloc*    data;

    data = get_data();
    if (data->start_heap == NULL || data->brk == data->start_heap)
        return;
    data->brk = data->start_heap;
    data->first_block = NULL;
    data->last_block = NULL;
    data->mem_left = 0;
    brk(data->start_heap);
}

void            free_heap(void)
{
    t_alloc*    data;
    t_block*    csr;
    size_t      gap;

    data = get_data();
    if ((csr = data->last_block) == NULL || !csr->free)
        return;
    while (csr->prev != NULL && csr->prev->free)
        csr = csr->prev;
    if (csr == data->first_block)
    {
        reset_heap();
        return;
    }
    gap = (size_t)data->last_block - (size_t)csr;
    gap /= BLOCK_SIZE;
    gap = (csr->size >= (gap * BLOCK_SIZE) || gap == 0) ? gap : gap - 1;
    if (gap == 0)
        return;
    gap *= BLOCK_SIZE;
    csr->size -= gap;
    csr->next = NULL;
    data->mem_left = 0;
    data->brk = (void*)csr + gap;
    brk(data->brk);
}

size_t          get_p2_idx(size_t n)
{
    size_t      mask;
    int         i;

    mask = 0b1000000000000000000000000000000000000000000000000000000000000000;
    i = 64;
    while (--i >= 0)
    {
        if (n & mask)
            return ((size_t)i);
        mask = mask >> 1;
    }
    return (0);
}

void            free(void *ptr)
{
    t_block*    b;
    t_alloc*    data;

    data = get_data();
    if (ptr == NULL || ptr < data->start_heap || ptr > data->brk)
        return;
    b = ptr - sizeof(t_block);
    b->free = 1;
    b->next_size = data->free_blocks;
    data->free_blocks = b;
    if (b->next != NULL && b->next->free)
        b = fusion_block(b);
    if (b->prev != NULL)
        fusion_block(b->prev);
}