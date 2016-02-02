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

static void *global_base = NULL;

t_block *find_free_node(t_block **last, size_t size)
{
  t_block *current;

  current = global_base;
  while (current && !(current->free && current->size >= size))
    {
      *last = current;
      current = current->next;
    }
  return (current);
}

void    *malloc(size_t t)
{
  t_block *bl;
  t_block *last;
  size_t size;

  if (t <= 0)
    return NULL;
  size = align4(t);
  if (global_base != NULL)
    {
      last = global_base;
      bl = need_space(last, size);
      if (!bl)
        return NULL;
      global_base = bl;
      bl->free = 0;
     }
  else
    {
      last = global_base;
      bl = find_free_node(&last, size);
      bl = glob_is_null(bl, last, size);
      global_base = bl;
    }
  printf("Malloc\n");
  return (bl+1);
}

t_block		*glob_is_null(t_block *bl, t_block *last, size_t size)
{
  if (!bl)
    {
      bl = need_space(last, size);
      if (!bl)
	    return NULL;
    }
  else
    {
      split_block(bl, size);
      bl->free = 0;
    }
  return (bl);
}

void  free(void *ptr)
{
  t_block *b;

  if (!ptr)
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
	global_base = NULL;
    }
  printf("free\n");
}

void    show_alloc_mem()
{
  t_block *bl;

  bl = global_base;
  while (bl != NULL)
  {
    //printf("break : %p\n%p - %p : %lu bytes\n", bl, bl->prev, bl->next, bl->size);
    bl = bl->prev;
  }
}
