/*
** management_block.c for management in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Mon Feb  1 08:12:22 2016 lina_a
** Last update Mon Feb  1 08:12:22 2016 lina_a
*/

#include <unistd.h>
#include <stdio.h>
#include "include/malloc.h"

t_block		*fusion_block(t_block *b)
{
  if (!b)
    return NULL;
  if (b->next && b->next->free)
    {
      b->size += SIZE_ALLOC + b->next->size;
      b->next = b->next->next;
      if (b->next)
	    b->next->prev = b;
    }
  return b;
}

void    split_block(t_block *bl, size_t size)
{
  t_block *new;

  new = bl;
  new->size = (bl->size - size) - SIZE_ALLOC;
  new->next = bl->next;
  new->prev = bl;
  new->free = 1;
  new->size = size;
  bl->next = new;
  if (new->next)
    new->next->prev = new;
}

t_block  *need_space(t_block *last, size_t size)
{
  t_block *block;
  void    *request;

  block = sbrk(0);
  request = sbrk(size + SIZE_ALLOC);
  if (request == (void*)-1)
    return NULL;
  block->size = size;
  block->next = NULL;
  block->prev = last;
  if (last)
    last->next = block;
  block->free = 0;
  return block;
}

t_block *get_block_ptr(void *ptr)
{
  return (t_block*)ptr - 1;
}
