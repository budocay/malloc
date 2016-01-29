#ifndef MY_MALLOC_H
# define MY_MALLOC_H

# include <stdlib.h>
# include <stdint.h>

typedef struct      s_block
{
    uint64_t        magic_number;
    size_t          size;
    struct s_block* next;
    struct s_block* prev;
}                   t_block;

# define PAGE_SIZE 16384
/* Taille d'une page mémoire */

# define SBRK_ERROR (void *)-1

# define MAGIC_NUMBER 42

void free_pages(void);
/* If the last pages are empty, deallocate them */

void*               malloc(size_t);
void                free(void *);
void*               realloc(void *, size_t);

t_block*            cast_mem(void *);
void*               new_block(void *, size_t);
void                add_block(void *);
void                remove_block(void *);
t_block*            get_block(size_t);

#endif /* MY_MALLOC_H */
