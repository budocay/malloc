//
// Created by lina_a on 28/01/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "malloc_tp.h"

static void *global_base = NULL;

t_block *get_block_ptr(void *ptr)
{
    return (t_block*)ptr - 1;
}

t_block *find_free_node(t_block **last, size_t size)
{
    t_block *current;

    current = global_base;
    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }
    return current;
}

t_block  *need_space(t_block *last, size_t size)
{
    t_block *block;
    void    *request;

    block = sbrk(0);
    request = sbrk(size + SIZE_ALLOC);
    if (request == (void*)-1)
        return NULL;
    block->size = size;
    block->next = NULL;
    block->prev = last;
    block->ptr = block->data;
    if(last)
        last->next = block;
    block->free = 0;
    return block;
}

void    *malloc(size_t t)
{
    t_block *bl;
    t_block *last;
    size_t size;

    if (t <= 0)
        return NULL;
    size = align4(t);
  if (global_base != NULL)
    {
        last = global_base;
        bl = need_space(last, size);
        if (!bl)
            return NULL;
        global_base = bl;
        bl->free = 0;
    }
    else
    {
        last = global_base;
        bl = find_free_node(&last, size);
        if (!bl)
        {
            bl = need_space(last, size);
            if (!bl)
                return NULL;
        }
        else
        {
            splitblock(bl, size);
            bl->free = 0;
        }
    }
    return (bl+1);
}

void    *realloc(void *ptr,size_t size)
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

void  free(void *ptr) {

    t_block *b;

    if (!ptr)
        return;
    b = get_block_ptr(ptr);
    b->free = 1;
    if (b->prev && b->prev->free)
        b = fusion_block(b->prev);
    if (b->next)
        fusion_block(b);
    else
    {
        if (b->prev)
            b->prev->next = NULL;
        else
            global_base = NULL;
    }
}

t_block *fusion_block(t_block *b)
{
    if (!b)
        return NULL;
    if (b->next && b->next->free)
    {
        b->size += SIZE_ALLOC + b->next->size;
        b->next = b->next->next;
        if (b->next)
            b->next->prev = b;
    }
    return b;
}

void    splitblock(t_block *bl, size_t size)
{
    t_block *new;

    new = (t_block *) bl->data + size;
    new->size = (bl->size - size) - SIZE_ALLOC;
    new->next = bl->next;
    new->prev = bl;
    new->free = 1;
    new->ptr = new->data;
    new->size = size;
    bl->next = new;
    if (new->next)
        new->next->prev = new;
}

void    *calloc(size_t size1, size_t size2)
{
    size_t size;;
    void    *ptr;

    size = size1 * size2;
    if (size < size1 * size2)
        return NULL;
    if ((ptr = malloc(size)) == NULL)
        return NULL;
    memset(ptr, 0, size);
    return ptr;
}
