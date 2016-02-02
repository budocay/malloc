//
// Created by lina_a on 02/02/16.
//


#include <stddef.h>
#include "include/malloc.h"

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
