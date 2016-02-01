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
#include "malloc.h"

static void *global_base = NULL;

void    *malloc(size_t t)
{
  t_block *bl;
  t_block *last;
  size_t size;

  if (t <= 0)
    return NULL;
  size = align4(t);
  bl = NULL;
  last = NULL;
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
    glob_is_null(bl, last, size);
  return (bl+1);
}

void	glob_is_null(t_block *bl, t_block *last, size_t size)
{
  last = global_base;
  bl = find_free_node(&last, size);
  if (!bl)
    {
      bl = need_space(last, size);
      if (!bl)
	return;
    }
  else
    {
      split_block(bl, size);
      bl->free = 0;
    }
}

void    *realloc(void *ptr,size_t size)
{
  t_block *block_ptr;
  void    *new_alloc_ptr;

  if (!ptr)
    return malloc(size);
  block_ptr = get_block_ptr(ptr);
  if(block_ptr->size >= size)
    return ptr;
  if ((new_alloc_ptr = malloc(size)) == NULL)
    return NULL;
  if(!new_alloc_ptr)
    {
      dprintf(2, "%m\n");
      return NULL;
    }
  memcpy(new_alloc_ptr, ptr, block_ptr->size);
  free(ptr);
  return new_alloc_ptr;
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
}

t_block *find_free_node(t_block **last, size_t size)
{
  t_block *current;

  current = global_base;
  while (current && !(current->free && current->size >= size))
    {
      *last = current;
      current = current->next;
    }
  return current;
}
