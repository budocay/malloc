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

    if (ptr == NULL)
        return malloc(size);
    else if (size == 0)
    {
        free(ptr);
        return (NULL);
    }
    block_ptr = get_block_ptr(ptr);
    if(block_ptr->size >= size)
        return ptr;
    if ((new_alloc_ptr = malloc(size)) == NULL)
        return (NULL);
    /* if(!new_alloc_ptr)
        return NULL; */
    memcpy(new_alloc_ptr, ptr, block_ptr->size);
    free(ptr);
    printf("Realloc\n");
    return (new_alloc_ptr);
}
