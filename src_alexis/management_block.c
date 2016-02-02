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

void            split_block(t_block *bl, size_t size)
{
    t_block*    new;

    new = bl;
    new->size = (bl->size - size) - SIZE_ALLOC;
    new->next = bl->next;
    new->prev = bl;
    new->free = 1;
    new->size = size;
    bl->next = new;
    if (new->next)
        new->next->prev = new;
}

t_block*        get_block_ptr(void *ptr)
{
    return ((ptr != NULL) ? (t_block*)ptr - 1 : NULL);
}

t_block*        create_block_with_mem_left(size_t size)
{
    size_t      length;
    t_block*    bl;
    t_alloc*    data;

    length = size + sizeof(t_block);
    data = get_data();
    if ((data->start_heap == NULL || data->brk == NULL) &&
        init_heap_data() < 0)
        return (NULL);
    if (data->mem_left < length)
        return (NULL);
    bl = data->brk - data->mem_left;
    bl->next_size = NULL;
    bl->size = size;
    bl->free = 0;
    data->mem_left -= length;
    return (bl);
}

t_block*        find_free_node(t_block **last, size_t size)
{
    t_block*    current;
    t_alloc*    data;

    data = get_data();
    if (data->first_block == NULL)
        return (NULL);
    current = data->first_block;
    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }
    return (current);
}