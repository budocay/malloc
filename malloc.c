//
// Created by lina_a on 28/01/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "malloc_tp.h"

void *global_base = NULL;

t_block *get_block_ptr(void *ptr)
{
    char *tmp;
    tmp = ptr;
    return (ptr = tmp -= SIZE_ALLOC);
}

t_block *find_free_node(t_block **last, size_t sze)
{
    t_block *current = global_base;
    while (current && !(current->free && current->size >= sze))
    {
        *last =current;
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
    assert((void*)block == request);
    if (request ==  (void*) -1)
        return NULL;
    block->size = size;
    block->next = NULL;
    if(last)
        last->next = block;
    block->free = 0;
    return block;
}

void    *malloc(size_t t)
{
    t_block *bl = NULL;
    t_block *last;

    if (t <= 0)
        return NULL;
    if (!global_base)
    {
        bl = need_space(NULL, t);
        if (!bl)
            return NULL;
        global_base = bl;
    }
    else
    {
        last = global_base;
        bl = find_free_node(&last, t);
        if (!bl)
        {
            bl = need_space(last, t);
            if (!bl)
                return NULL;
        }
        else
        {
            bl->free = 0;
        }
    }
    return bl+1;
}

void    *realloc(void *ptr,size_t size)
{
    t_block *block_ptr;
    void    *new_alloc_ptr;

    if (!ptr)
        return malloc(size);
    block_ptr = get_block_ptr(ptr);
    if(block_ptr->size >= size)
    {
        return ptr;
    }
    new_alloc_ptr = malloc(size);
    if(!new_alloc_ptr)
    {
        dprintf(2, "%m\n");
        return NULL;
    }
    memcpy(new_alloc_ptr, ptr, block_ptr->size);
    free(ptr);
    return new_alloc_ptr;
}

void  free(void *ptr)
{
    t_block *b;
    if (valid_addr(ptr))
    {
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
            brk(b);
        }
    }

    /*t_block *blk_ptr;
    if (!ptr)
        return;
    blk_ptr = get_block_ptr(ptr);
    assert(blk_ptr->free == 0);
    blk_ptr->free = 1;*/
}

t_block *fusion_block(t_block *b)
{
    if (b->next && b->next->free)
    {
        b->size += SIZE_ALLOC + b->next->size;
        b->next = b->next->next;
        if (b->next)
            b->next->prev = b;
    }
    return b;
}

int     valid_addr(void *p)
{
    if (global_base)
    {
        if (p > global_base && p < sbrk(0))
        {
            return (p == (get_block_ptr(p))->ptr);
        }
    }
    return 0;
}