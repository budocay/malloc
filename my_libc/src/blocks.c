/*
** blocks for PSU_2019_malloc
**
** Made by pirou_g in /home/pirou_g/piscine_tek2/PSU_2019_malloc
** Login   <pirou_g@epitech.net>
**
** Started on     28/01/16 21:31
** Last update on 28/01/16 21:31
*/

#include <stdio.h>
#include "my_malloc.h"

void            dump_header(t_block *block)
{
    if (block == NULL)
        return;
    fprintf(stderr, "====\nMagic Number = %ld\nSize = %ld\nnext = %p\nprev = %p\n=====\n", block->magic_number,
            block->size, block->next, block->prev);
}

static t_block* freed = NULL;

t_block*        cast_mem(void *mem)
{
    if (mem == NULL || (size_t)mem <= sizeof(t_block))
        return (NULL);
    mem -= sizeof(t_block);
    return (mem);
}

void*           new_block(void *mem, size_t size)
{
    t_block*    block;

    fprintf(stderr, "new_block\n");
    if ((block = mem) == NULL || (size_t)mem <= sizeof(t_block))
        return (NULL);
    block->magic_number = MAGIC_NUMBER;
    block->size = size;
    block->next = NULL;
    block->prev = NULL;
    return (mem + sizeof(t_block));
}

void            add_block(void *mem)
{
    t_block*    block;
    t_block*    csr;
    void*       ptr;

    fprintf(stderr, "add_block\n");
    if ((block = cast_mem(mem)) == NULL)
        return;
    if ((csr = freed) == NULL)
    {
        block->next = NULL;
        block->prev = NULL;
        freed = block;
        return;
    }
    while (csr->next != NULL)
    {
        ptr = csr;
        ptr += sizeof(t_block);
        ptr += csr->size;
        if (csr == block || csr->next == block)
            return;
        if (ptr == block)
        {
            csr->size += block->size;
            return;
        }
        else if ((size_t)ptr > (size_t)block)
        {
            block->next = csr;
            block->prev = csr->prev;
            csr->prev = block;
            return;
        }
        csr = csr->next;
    }
    block->next = NULL;
    block->prev = csr;
    csr->next = block;
}

void            remove_block(void *mem)
{
    t_block*    block;

    fprintf(stderr, "remove_block\n");
    if ((block = mem) == NULL)
        return;
    if (block == freed)
    {
        if (freed->prev == NULL && freed->next == NULL) {
            freed = NULL;
        }
        else
            freed = freed->next;
    }
    else
    {
        if (block->prev != NULL)
            block->prev->next = block->next;
        if (block->next != NULL)
            block->next->prev = block->prev;
    }
    block->next = NULL;
    block->prev = NULL;
}

t_block*        get_block(size_t size)
{
    t_block*    csr;
    void*       ptr;

    fprintf(stderr, "get_block\n");
    if ((csr = freed) == NULL)
        return (NULL);
    while (csr->next != NULL)
    {
        //fprintf(stderr, "=====\nloop get_block\n=====\n");
        if (csr->size >= size)
        {
            remove_block(csr);
            ptr = csr;
            ptr += sizeof(t_block);
            return (ptr);
        }
        csr = csr->next;
    }
    if (csr->size >= size)
    {
        remove_block(csr);
        ptr = csr;
        ptr += sizeof(t_block);
        return (ptr);
    }
    return (NULL);
}