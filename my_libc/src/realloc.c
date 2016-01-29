/*
** realloc for PSU_2019_malloc
**
** Made by pirou_g in /home/pirou_g/piscine_tek2/PSU_2019_malloc
** Login   <pirou_g@epitech.net>
**
** Started on     25/01/16 22:38
** Last update on 25/01/16 22:38
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my_malloc.h"

/* void*           realloc_in_block(t_block* block, t_block* dest)
{
    uint8_t*    data_block;
    uint8_t*    data_dest;

    fprintf(stderr, "realloc_in_block\n");
    if (block == NULL || dest == NULL)
        return (NULL);
    data_block = (uint8_t *)block + sizeof(t_block);
    data_dest = (uint8_t *)dest + sizeof(t_block);
    memcpy(data_dest, data_block, block->size);
    add_block(data_block);
    return (data_dest);
}

void*           realloc_in_new_block(t_block* block, size_t size)
{
    void*       dest;
    uint8_t*    data;

    fprintf(stderr, "realloc_in_new_block\n");
    if (block == NULL || (dest = malloc(size)) == NULL)
        return (NULL);
    data = (uint8_t *)block + sizeof(t_block);
    memcpy(dest, data, block->size);
    add_block(data);
    return (dest);
} */

void*           realloc(void *ptr, size_t size)
{
    void*       dest;
    t_block*    block;

    fprintf(stderr, "realloc\n");
    if (ptr != NULL && size == 0)
        free(ptr);
    else if (ptr == NULL)
        return (malloc(size));
    if ((block = cast_mem(ptr)) == NULL) {
        /* fprintf(stderr, "cast failed in realloc\n"); */
        return (NULL);
    }
    if (size <= block->size)
        return (ptr);
    /* if ((dest = get_block(size)) != NULL)
        return (realloc_in_block(block, dest));
    return (realloc_in_new_block(block, size)); */
    if ((dest = malloc(size)) == NULL)
        return (NULL);
    memcpy(dest, ptr, block->size);
    free(ptr);
    return (dest);
}