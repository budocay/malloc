//
// Created by lina_a on 02/02/16.
//

#include <stdio.h>
#include "include/malloc.h"

void            show_alloc_mem(void)
{
    t_block*    bl;
    t_alloc*    data;

    data = get_data();
    if ((bl = data->first_block) == NULL)
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

    data = get_data();
    if ((bl = data->first_block) == NULL)
        return;
    printf("break : %p\n", data->brk);
    while (bl != NULL)
    {
        printf("%p - %p : %lu bytes\nfree : %d\n", bl, (void*)bl + bl->size + sizeof(t_block), bl->size, bl->free);
        bl = bl->next;
    }
}