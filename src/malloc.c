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
#include "malloc.h"

static t_alloc  data = {NULL, NULL, NULL, NULL, NULL, 0, 0};

t_alloc*        get_data(void)
{
    return (&data);
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
    data.page_size = (size_t)getpagesize();
    return (0);
}

t_block*        expand_and_create_block(size_t size)
{
    if (brk(data.brk + BLOCK_SIZE + size) < 0)
        return (NULL);
    data.mem_left += BLOCK_SIZE + size;
    data.brk += BLOCK_SIZE + size;
    return (create_block_with_mem_left(size));
}

void*           malloc(size_t t)
{
    t_block*    bl;
    size_t      size;

    size = align4(t);
    if (data.page_size == 0 && init_heap_data() < 0)
        return (NULL);
    if (data.mem_left >= (size + sizeof(t_block)))
    {
	    if ((bl = create_block_with_mem_left(size)) == NULL)
            return (NULL);
        insert_block(bl);
        return (bl + 1);
    }
    else if ((bl = test_optimize_malloc(size)) != NULL)
        return (bl);
    if ((bl = expand_and_create_block(size)) == NULL)
      return (NULL);
    insert_block(bl);
    return (bl + 1);
}