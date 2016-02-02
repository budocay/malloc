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

    fprintf(stderr, "fusion_block\n");
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

    fprintf(stderr, "split_block\n");
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

t_block*        need_space(t_block *last, size_t size)
{
    t_block*    block;
    void*       request;

    fprintf(stderr, "need_space\n");
    block = sbrk(0);
    request = sbrk(size + SIZE_ALLOC);
    if (request == (void*)-1)
        return (NULL);
    block->size = size;
    block->next = NULL;
    block->prev = last;
    if (last)
        last->next = block;
    block->free = 0;
    return (block);
}

t_block*        get_block_ptr(void *ptr)
{
    return ((ptr != NULL) ? (t_block*)ptr - 1 : NULL);
}
