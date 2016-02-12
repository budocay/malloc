/*
** management_block.c for management in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Mon Feb  1 08:12:22 2016 lina_a
** Last update Mon Feb  1 08:12:22 2016 lina_a
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "include/malloc.h"

t_block*        fusion_block(t_block *b)
{
    t_block*    cpy;

    if (b == NULL)
        return (NULL);
    cpy = b->next;
    if (b->next != NULL && b->next->free)
    {
        b->size += SIZE_ALLOC + b->next->size;
        b->next = b->next->next;
        if (b->next != NULL)
            b->next->prev = b;
        memset(cpy, 0, sizeof(t_block));
    }
    return (b);
}

t_block*        split_block(t_block *bl, size_t size)
{
    t_block*    new;
    void*       ptr;

    if (bl == NULL || !(bl->free) ||
        ((long)(bl->size - sizeof(t_block))) < (long)size)
        return (NULL);
    ptr = bl;
    ptr += (bl->size - size);
    new = ptr;
    new->prev = bl;
    new->next = bl->next;
    new->size = size;
    new->free = 0;
    new->next_size = NULL;
    bl->next = new;
    bl->size -= (size + sizeof(t_block));
    return (new);
}

t_block*        get_block_ptr(void *ptr)
{
    return ((ptr != NULL) ? (t_block*)ptr - 1 : NULL);
}

t_block*        extract_free_node(t_block* block)
{
    t_alloc*    data;

    if (block == NULL)
        return (NULL);
    data = get_data();
    block->free = 0;
    data->free_blocks = block->next_size;
    block->next_size = NULL;
    return (block);
}

t_block*        find_free_node(size_t size)
{
    t_block*    current;
    t_alloc*    data;

    data = get_data();
    if ((current = data->free_blocks) == NULL)
        return (NULL);
    if (current->size >= size)
        return (extract_free_node(current));
    while (current->next_size != NULL)
    {
        if (current->next_size->size >= size)
            return (extract_free_node(current->next_size));
        current = current->next;
    }
    return (NULL);
}
