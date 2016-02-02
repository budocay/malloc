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

#define BLOCK_SIZE   4096
#define BIG_IDX     (BLOCK_SIZE / sizeof(void*))
#define GET_IDX(x)  ((x < (BLOCK_SIZE - sizeof(void*))) ? x / sizeof(void*) : BIG_IDX)
#define SIZE_ALLOC  sizeof(t_block)
#define align4(x)   (((((x)-1)>>2)<<2)+4)

#include <stddef.h>

typedef struct      s_block
{
    size_t          size;
    struct s_block* next;
    struct s_block* prev;
    struct s_block* next_size;
    size_t          free;
}                   t_block;

typedef struct      s_alloc
{
    t_block*        first_block;
    void*           start_heap;
    void*           brk;
    size_t          mem_left;
    void*           global_base;
    t_block*        free_blocks[BIG_IDX + 1];
}                   t_alloc;

void*               malloc(size_t t);
void                free(void * ptr);
void*               realloc(void * ptr, size_t size);
t_block*            fusion_block(t_block *b);
void                split_block(t_block *bl, size_t size);
void*               calloc(size_t size1, size_t size2);
t_block*            find_free_node(t_block **last, size_t size);
t_block*            need_space(t_block *last, size_t size);
t_block*	        glob_is_null(t_block *, t_block*, size_t);
t_block*            get_block_ptr(void *ptr);
void                show_alloc_mem();
t_alloc*            get_data(void);

#endif /* MALLOC_H_! */
