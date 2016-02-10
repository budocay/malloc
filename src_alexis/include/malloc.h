/*
** malloc.h for malloc in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Mon Feb  1 10:21:22 2016 lina_a
** Last update Mon Feb  1 10:21:22 2016 lina_a
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#define BLOCK_SIZE  getpagesize()
#define SIZE_ALLOC  sizeof(t_block)
#define align4(x)   (((((x)-1)>>2)<<2)+4)

#include <stddef.h>
#include <stdint.h>

typedef struct      s_block
{
    size_t          size;
    struct s_block* next;
    struct s_block* prev;
    struct s_block* next_size;
    uint32_t        free;
}                   t_block;

typedef struct      s_alloc
{
    t_block*        first_block;
    t_block*        last_block;
    void*           start_heap;
    void*           brk;
    size_t          mem_left;
    t_block*        free_blocks[64];
}                   t_alloc;

void*               malloc(size_t t);
void                free(void * ptr);
void*               realloc(void * ptr, size_t size);
t_block*            fusion_block(t_block *b);
void*               split_block(t_block *bl, size_t size);
void*               calloc(size_t size1, size_t size2);
t_block*            find_free_node(size_t size);
t_block*            get_block_ptr(void *ptr);
void                show_alloc_mem(void);
void                show_mem(void);
t_alloc*            get_data(void);
t_block*            create_block_with_mem_left(size_t size);
int                 init_heap_data(void);
size_t              get_p2_idx(size_t n);

#endif /* MALLOC_H_! */
