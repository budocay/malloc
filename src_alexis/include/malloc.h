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

#define SIZE_ALLOC sizeof(t_block)
#define align4(x) (((((x)-1)>>2)<<2)+4)

#include <stddef.h>

typedef struct s_block{
    size_t size;
    struct s_block *next;
    struct s_block *prev;
    int     free;
}t_block;

void *malloc(size_t t);
void free(void * ptr);
void *realloc(void * ptr, size_t size);
t_block *fusion_block(t_block *b);
void    split_block(t_block *bl, size_t size);
void    *calloc(size_t size1, size_t size2);
t_block *find_free_node(t_block **last, size_t size);
t_block  *need_space(t_block *last, size_t size);
t_block	*glob_is_null(t_block *, t_block*, size_t);
t_block *get_block_ptr(void *ptr);
void    show_alloc_mem();

#endif /* MALLOC_H_! */
