/*
** malloc.c for malloc in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Mon Feb  1 08:07:51 2016 lina_a
** Last update Mon Feb  1 08:07:51 2016 lina_a
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/malloc.h"

static t_alloc  data = {NULL, NULL, NULL, NULL, 0/*, {NULL}*/};

t_alloc*        get_data(void)
{
    return (&data);
}

void            insert_block(t_block *bl)
{
    if (bl == NULL)
        return;
    if (data.first_block == NULL)
    {
        data.first_block = bl;
        data.last_block = bl;
        bl->next = NULL;
        bl->prev = NULL;
        return;
    }
    bl->next = NULL;
    bl->prev = data.last_block;
    data.last_block->next = bl;
    data.last_block = bl;
}

int             init_heap_data(void)
{
    size_t      padding;

    if ((data.start_heap = sbrk(0)) == (void*)-1)
        return (-1);
    if ((padding = 4 - ((size_t)data.start_heap % 4)) > 0 &&
        brk(data.start_heap + padding) < 0)
        return (-2);
    data.start_heap += padding;
    data.brk = data.start_heap;
    data.mem_left = 0;
    return (0);
}


t_block*        expand_and_create_block(size_t size)
{
    if (((data.start_heap == NULL || data.brk == NULL) &&
         init_heap_data()) < 0 || sbrk(BLOCK_SIZE + size) == (void*)-1)
        return (NULL);
    data.mem_left += BLOCK_SIZE + size;
    data.brk += BLOCK_SIZE + size;
    return (create_block_with_mem_left(size));
}

void*           malloc(size_t t)
{
    t_block*    bl;
    size_t      size;

    if (!t)
        return (NULL);
    size = align4(t);
    if (data.first_block != NULL &&
        (bl = find_free_node(size)) != NULL)
    {
        split_block(bl, size);
        return (bl + 1);
    }
    else if (data.mem_left >= (size + sizeof(t_block)))
    {
        if ((bl = create_block_with_mem_left(size)) == NULL)
            return (NULL);
        insert_block(bl);
        return (bl + 1);
    }
    if ((bl = expand_and_create_block(size)) == NULL)
        return (NULL);
    insert_block(bl);
    return (bl + 1);
}