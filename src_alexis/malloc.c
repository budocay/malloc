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

static t_alloc  data = {NULL, NULL, NULL, NULL, 0/*, {NULL}*/};

t_alloc*        get_data(void)
{
    return (&data);
}

t_block*        find_free_node(t_block **last, size_t size)
{
    t_block*    current;

    if (data.first_block == NULL)
        return (NULL);
    current = data.first_block;
    /* fprintf(stderr, "find_free_node : data.first_block = %p\n", data.first_block);
    fprintf(stderr, "idem : data.size = %ld\n", data.first_block->size);
    fprintf(stderr, "idem : data.next = %p\n", data.first_block->next); */
    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }
    return (current);
}

/* void*           malloc(size_t t)
{
    t_block*    bl;
    t_block*    last;
    size_t      size;

    if (!t)
        return (NULL);
    size = align4(t);
    last = data.first_block;
    if (last != NULL)
    {
        bl = need_space(last, size);
        if (bl == NULL)
            return (NULL);
        data.first_block = bl;
        bl->free = 0;
    }
    else
    {
        bl = find_free_node(&last, size);
        bl = glob_is_null(bl, last, size);
        data. = bl;
    }
    fprintf(stderr, "Malloc\n");
    return (bl+1);
} */

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

t_block*        create_block_with_mem_left(size_t size)
{
    size_t      length;
    t_block*    bl;

    length = size + sizeof(t_block);
    if ((data.start_heap == NULL || data.brk == NULL) &&
        init_heap_data() < 0)
        return (NULL);
    if (data.mem_left < length)
        return (NULL);
    bl = data.brk - data.mem_left;
    bl->next_size = NULL;
    bl->size = size;
    bl->free = 0;
    data.mem_left -= length;
    return (bl);
}

t_block*        expand_and_create_block(size_t size)
{
    if (((data.start_heap == NULL || data.brk == NULL) &&
         init_heap_data()) < 0 || brk(data.brk + BLOCK_SIZE + size) < 0)
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
    /* fprintf(stderr, "Malloc\n"); */
    size = align4(t);
    if (data.first_block != NULL &&
        (bl = find_free_node(&(data.first_block), size)) != NULL)
        return (bl + 1);
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

    if (ptr == NULL || ptr < data.start_heap || ptr > data.brk)
        return;
    // b = get_block_ptr(ptr);
    b = (ptr - sizeof(t_block));
    /* fprintf(stderr, "free address of block = %p\n", b);
    fprintf(stderr, "free size of block = %ld\n", b->size); */
    b->free = 1;
    if (b->next != NULL && b->next->free)
        b = fusion_block(b);
    if (b->prev != NULL)
        fusion_block(b->prev);
    else
    {
        if (b->prev != NULL)
            b->prev->next = b->next;
        if (b->next != NULL)
            b->next->prev = b->prev;
        else
            data.first_block = NULL;
    }
    //fprintf(stderr, "free\n");
}

void            show_alloc_mem(void)
{
    t_block*    bl;

    if ((bl = data.first_block) == NULL)
        return;
    printf("break : %p\n", data.brk);
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

    if ((bl = data.first_block) == NULL)
        return;
    printf("start of heap : %p\n", data.start_heap);
    printf("break : %p\n", data.brk);
    while (bl != NULL)
    {
        printf("%p - %p : %lu bytes\nfree : %d\n", bl, (void*)bl + bl->size + sizeof(t_block), bl->size, bl->free);
        bl = bl->next;
    }
}