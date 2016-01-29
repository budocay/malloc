/*
** malloc for PSU_2019_malloc
**
** Made by pirou_g in /home/pirou_g/piscine_tek2/PSU_2019_malloc
** Login   <pirou_g@epitech.net>
**
** Started on     25/01/16 22:38
** Last update on 25/01/16 22:38
*/

#include <unistd.h>
#include <stdio.h>
#include "my_malloc.h"

static size_t   mem_left = 0;

void*           _sbrk(size_t size)
{
    void*       heap;
    size_t      to_allocate;
    size_t      padding;
    size_t      nb_pages;

    if ((heap = sbrk(0)) == SBRK_ERROR) {
        return (NULL);
    }
    heap -= mem_left;
    padding = sizeof(size_t) - ((size_t)heap % sizeof(size_t));
    size += (sizeof(size_t) - (size % sizeof(size_t)));
    to_allocate = padding + size + sizeof(t_block);
    heap += padding;
    if (mem_left >= to_allocate)
    {
        mem_left -= to_allocate;
        return (new_block(heap, size));
    }
    nb_pages = (to_allocate / PAGE_SIZE) + 1;
    if (sbrk(nb_pages * PAGE_SIZE) == SBRK_ERROR) {
        return (NULL);
    }
    mem_left += (nb_pages * PAGE_SIZE) - to_allocate;
    return (new_block(heap, size));
}

void*           malloc(size_t size)
{
    void*       block;

    if ((block = get_block(size)) != NULL)
        return (block);
    return (_sbrk(size));
}