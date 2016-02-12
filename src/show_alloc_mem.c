/*
** show_alloc_mem.c for show_alloc_mem in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Thu Feb  4 12:53:57 2016 lina_a
** Last update Thu Feb  4 12:53:57 2016 lina_a
*/

#include <stdio.h>
#include "malloc.h"

void            show_alloc_mem(void)
{
    t_block*    bl;
    t_alloc*    data;

    if ((data = get_data()) == NULL || (bl = data->first_block) == NULL)
        return;
    printf("break : %p\n", data->brk);
    while (bl != NULL)
    {
        if (!bl->free)
            printf("%p - %p : %lu bytes\n", bl, (void*)bl + bl->size, bl->size);
        bl = bl->next;
    }
}

void            show_mem(void)
{
    t_block*    bl;
    t_alloc*    data;

    if ((data = get_data()) == NULL || (bl = data->first_block) == NULL)
        return;
    printf("start of heap : %p\n", data->start_heap);
    printf("break : %p\n", data->brk);
    while (bl != NULL)
    {
        printf("%p - %p : %lu bytes\nfree : %d\n", bl, (void*)bl + bl->size
	       + sizeof(t_block), bl->size, bl->free);
        bl = bl->next;
    }
}