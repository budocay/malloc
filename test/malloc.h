/*
** malloc for malloc
**
** Made by pirou_g in /home/pirou_g/piscine_tek2/malloc
** Login   <pirou_g@epitech.net>
**
** Started on     31/01/16 20:53
** Last update on 31/01/16 20:53
*/

#ifndef MALLOC_MALLOC_H_H
#define MALLOC_MALLOC_H_H

#include <stdlib.h>

#define BLOC_SIZE       4096
#define GET_FREE_IDX(x) ((x < BLOCK_SIZE) ? (int)(x / sizeof(void*)) : (BLOC_SIZE) / sizeof(void*))

typedef struct          s_header
{
    size_t              size;
    struct s_header*    prev_address;
    struct s_header*    next_address;
    struct s_header*    prev_size;
    struct s_header*    next_size;
}                       t_header;

typedef struct          s_alloc_data
{
    t_header*           first_block;
    t_header*           last_block;
    void*               start_heap;
    void*               end_heap;
    size_t              unassigned_mem;
}                       t_alloc_data;

/* Free blocks are sorted by range of size in an array of PAGE_SIZE + sizeof(void *)
 * For example for a page size of 4096 Bytes on 64 bits computer
 * an array has (4096 / 8) + 1 = 512 + 1 = 513 indexes
 * 512 first entries are list of blocks which size is inferior to BLOC_SIZE
 * last entrie is for allocations of multiple blocs (e.g. an alloc of 5000 bytes)
*/

typedef struct          s_free_data
{
    t_header*           first_block;
    t_header*           last_block;
    t_header*           blocks[(BLOC_SIZE / sizeof(void*)) + 1];
}                       t_free_data;

void*                   malloc(size_t);
void                    free(void*);
void*                   calloc(size_t, size_t);
void*                   realloc(void*, size_t);

void                    show_alloc_mem(void);
void                    show_free_mem(void);

#endif //MALLOC_MALLOC_H_H
