/*
** blocks for PSU_2019_malloc
**
** Made by pirou_g in /home/pirou_g/piscine_tek2/PSU_2019_malloc
** Login   <pirou_g@epitech.net>
**
** Started on     28/01/16 21:31
** Last update on 28/01/16 21:31
*/

#include "my_malloc.h"

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

    if ((block = cast_mem(mem)) == NULL)
        return;
    if ((csr = freed) == NULL)
    {
        block->next = block;
        block->prev = block;
        freed = block;
        return;
    }
    while (csr->next != freed)
    {
        if ((ptr = csr + sizeof(t_block) + csr->size) == block)
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
    }
    block->next = freed;
    block->prev = freed->prev;
    freed->prev->next = block;
    freed->prev = block;
}

void            remove_block(void *mem)
{
    t_block*    block;

    if ((block = cast_mem(mem)) == NULL)
        return;
    if (block == freed)
    {
        if (freed->prev == freed && freed->next == freed)
            freed = NULL;
        else
        {
            freed->prev->next = freed->next;
            freed->next->prev = freed->prev;
            freed = freed->next;
        }
    }
    else
    {
        block->prev->next = block->next;
        block->next->prev = block->prev;
    }
    block->next = NULL;
    block->prev = NULL;
}

t_block*        get_block(size_t size)
{
    t_block*    csr;
    void*       ptr;

    if ((csr = freed) == NULL)
        return (NULL);
    while (csr->next != freed)
    {
        if (csr->size >= size)
        {
            remove_block(ptr = csr + sizeof(t_block));
            return (ptr);
        }
    }
    if (csr->size >= size)
    {
        remove_block(ptr = csr + sizeof(t_block));
        return (ptr);
    }
    return (NULL);
}