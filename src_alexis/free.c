//
// Created by lina_a on 02/02/16.
//


#include <stddef.h>
#include <unistd.h>
#include "include/malloc.h"

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
    if (csr == data->first_block) {
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

void            free(void *ptr)
{
    t_block*    b;
    t_alloc*    data;

    data = get_data();
    if (ptr == NULL || ptr < data->start_heap || ptr > data->brk)
        return;
    b = get_block_ptr(ptr);
    b->free = 1;
    if (b->next != NULL && b->next->free)
        b = fusion_block(b);
    if (b->prev != NULL)
        fusion_block(b->prev);
    free_heap();
    /* else
    {
        if (b->prev != NULL)
            b->prev->next = b->next;
        if (b->next != NULL)
            b->next->prev = b->prev;
        else
            data->first_block = NULL;
    } */
}
