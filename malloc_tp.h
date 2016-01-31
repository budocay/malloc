//
// Created by lina_a on 28/01/16.
//

#ifndef MALLOC_MALLOC_TP_H
#define MALLOC_MALLOC_TP_H

#include <stddef.h>
#include <glob.h>

#define SIZE_ALLOC sizeof(t_block)

#define align4(x) (((((x)-1)>>2)<<2)+4)

typedef struct s_block{
    size_t size;
    struct s_block *next;
    struct s_block *prev;
    int     free;
    void    *ptr;
    char    data[1];
}t_block;

void *malloc(size_t t);
void free(void * ptr);
void *realloc(void * ptr, size_t size);
t_block *fusion_block(t_block *b);
void    splitblock(t_block *bl, size_t size);
void    *calloc(size_t size1, size_t size2);
t_block *find_free_node(t_block **last, size_t size);
t_block  *need_space(t_block *last, size_t size);

#endif //MALLOC_MALLOC_TP_H
