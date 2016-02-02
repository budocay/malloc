/*
** realloc.c for realloc in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Tue Feb  2 11:23:35 2016 lina_a
** Last update Tue Feb  2 11:23:35 2016 lina_a
*/

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "include/malloc.h"

void*           realloc(void *ptr, size_t size)
{
    t_block*    block_ptr;
    void*       new_alloc_ptr;

    if (ptr == NULL)
        return (malloc(size));
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
    memcpy(new_alloc_ptr, ptr, block_ptr->size);
    free(ptr);
    fprintf(stderr, "Realloc\n");
    return (new_alloc_ptr);
}
