//
// Created by lina_a on 02/02/16.
//

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "include/malloc.h"

void    *realloc(void *ptr, size_t size)
{
    t_block *block_ptr;
    void    *new_alloc_ptr;

    if (!ptr)
        return malloc(size);
    block_ptr = get_block_ptr(ptr);
    if(block_ptr->size >= size)
        return ptr;
    if ((new_alloc_ptr = malloc(size)) == NULL)
        return NULL;
    if(!new_alloc_ptr)
    {
        dprintf(2, "%m\n");
        return NULL;
    }
    memcpy(new_alloc_ptr, ptr, block_ptr->size);
    free(ptr);
    return new_alloc_ptr;
}
