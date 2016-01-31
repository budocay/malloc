/*
** malloc for malloc
**
** Made by pirou_g in /home/pirou_g/piscine_tek2/malloc
** Login   <pirou_g@epitech.net>
**
** Started on     31/01/16 20:57
** Last update on 31/01/16 20:57
*/

#include <string.h>
#include <stdio.h>
#include "malloc.h"

static t_alloc_data alloc_data = {NULL, NULL, NULL, NULL, 0};
static t_free_data  free_data = {NULL, NULL, {NULL}};

void*               malloc(size_t size)
{
    (void)size;
    return (NULL);
}

void                free(void* ptr)
{
    (void)ptr;
}

void*               calloc(size_t n, size_t size)
{
    void*           dest;

    size *= n;
    if ((dest = malloc(size)) == NULL)
        return (NULL);
    return (memset(dest, 0, size));
}

void*               realloc(void* ptr, size_t size)
{
    t_header*       header;
    void*           dest;

    if (ptr == NULL)
        return (malloc(size));
    else if (size == 0)
    {
        free(ptr);
        return (NULL);
    }
    header = (ptr - sizeof(t_header));
    if (header->size >= size)
        return (ptr);
    if ((dest = malloc(size)) == NULL)
        return (NULL);
    memcpy(dest, ptr, header->size);
    free(ptr);
    return (dest);
}

void                show_alloc_mem(void)
{
    t_header*       csr;

    if ((csr = alloc_data.first_block) == NULL)
        return;
    fprintf(stdout, "===== Start of show_alloc_mem =====\n");
    while (csr != NULL)
    {
        fprintf(stdout, "Size of block : %ld\n", csr->size);
        fprintf(stdout, "Address of previous block in address : %p\n", csr->prev_address);
        fprintf(stdout, "Address of next block in address : %p\n", csr->next_address);
        fprintf(stdout, "*****\n");
        csr = csr->next_address;
    }
    fprintf(stdout, "===== End of show_alloc_mem =====\n");
}

void                show_free_mem(void)
{
    t_header*       csr;

    if (free_data.first_block == NULL)
        return;
    fprintf(stdout, "===== Start of show_free_mem =====\n");
    while (csr != NULL)
    {
        fprintf(stdout, "Size of block : %ld\n", csr->size);
        fprintf(stdout, "Address of previous block in address : %p\n", csr->prev_address);
        fprintf(stdout, "Address of next block in address : %p\n", csr->next_address);
        fprintf(stdout, "Address of previous block in size : %p\n", csr->prev_size);
        fprintf(stdout, "Address of next block in size : %p\n", csr->next_size);
        fprintf(stdout, "*****\n");
        csr = csr->next_address;
    }
    fprintf(stdout, "===== End of show_free_mem =====\n");
}