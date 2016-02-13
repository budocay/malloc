/*
** malloc.c for malloc in /home/pirou_g/ClionProjects/PSU_2015_malloc/src
**
** Made by pirou_g
** Login   <pirou_g@epitech.net>
**
** Started on  Mon Feb  13 08:43:32 2016 pirou_g
** Last update Mon Feb  13 08:43:32 2016 pirou_g
*/

#include <stdlib.h>
#include <unistd.h>
#include "malloc.h"

t_block*        create_page_size_bloc()
{
    t_alloc*    data;
    size_t      page_size;
    void*       ptr_brk;

    data = get_data();
    page_size = data->page_size;
    ptr_brk = data->brk + page_size + sizeof(t_block);
    if (brk(ptr_brk) < 0)
        return (NULL);
    data->brk = ptr_brk;
    data->mem_left += page_size + sizeof(t_block);
    return create_block_with_mem_left(page_size);
}

void*           test_optimize_malloc(size_t size)
{
    t_block*    bl;
    t_alloc*    data;

    data = get_data();
    if (data->first_block != NULL &&
        (bl = find_free_node(size)) != NULL)
    {
        if (bl->size > (size + sizeof(t_block)))
        {
            if ((bl = split_block(bl, size)) == NULL)
                return (NULL);
            insert_block(bl);
        }
        return (bl + 1);
    }
    else if (size >= data->page_size &&
             size <= (data->page_size + sizeof(t_block) + 4))
    {
        if ((bl = create_page_size_bloc()) == NULL)
            return (NULL);
        insert_block(bl);
        return (bl + 1);
    }
    return (NULL);
}
