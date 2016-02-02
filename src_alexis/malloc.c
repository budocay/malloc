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

/* static void*  global_base = NULL; */

static t_alloc  data = {NULL, NULL, NULL, 0, NULL, {NULL}};

t_alloc*        get_data(void)
{
    return (&data);
}

t_block*        find_free_node(t_block **last, size_t size)
{
    t_block*    current;

    current = data.global_base;
    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }
    return (current);
}

void*           malloc(size_t t)
{
    t_block*    bl;
    t_block*    last;
    size_t      size;

    if (!t)
        return (NULL);
    size = align4(t);
    last = data.global_base;
    if (last != NULL)
    {
        bl = need_space(last, size);
        if (bl == NULL)
            return (NULL);
        data.global_base = bl;
        bl->free = 0;
    }
    else
    {
        bl = find_free_node(&last, size);
        bl = glob_is_null(bl, last, size);
        data.global_base = bl;
    }
    fprintf(stderr, "Malloc\n");
    return (bl+1);
}

t_block*        glob_is_null(t_block *bl, t_block *last, size_t size)
{
    if (bl == NULL)
    {
        if ((bl = need_space(last, size)) == NULL)
            return (NULL);
    }
    else
    {
        split_block(bl, size);
        bl->free = 0;
    }
    return (bl);
}

void            free(void *ptr)
{
    t_block*    b;

    if (ptr == NULL)
        return;
    b = get_block_ptr(ptr);
    b->free = 1;
    if (b->prev && b->prev->free)
        b = fusion_block(b->prev);
    if (!b->next)
        fusion_block(b);
    else
    {
        if (b->prev)
            b->prev->next = NULL;
        else
            data.global_base = NULL;
    }
    fprintf(stderr, "free\n");
}

void            show_alloc_mem()
{
    t_block*    bl;

    bl = data.global_base;
    while (bl != NULL)
    {
        //printf("break : %p\n%p - %p : %lu bytes\n", bl, bl->prev, bl->next, bl->size);
        bl = bl->prev;
    }
}
