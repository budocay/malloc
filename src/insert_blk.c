/*
** inster_blk.c for insert_blk in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Fri Feb 12 11:32:52 2016 lina_a
** Last update Fri Feb 12 11:32:52 2016 lina_a
*/

#include <unistd.h>
#include "include/malloc.h"

void            insert_block(t_block *bl)
{
  t_alloc	*data;

  if (bl == NULL)
    return;
  data = get_data();
  if (data->first_block == NULL)
    {
      data->first_block = bl;
      data->last_block = bl;
      bl->next = NULL;
      bl->prev = NULL;
      return;
    }
  bl->next = NULL;
  bl->prev = data->last_block;
  data->last_block->next = bl;
  data->last_block = bl;
}

t_block*        create_block_with_mem_left(size_t size)
{
  size_t      length;
  t_block*    bl;
  t_alloc*    data;

  length = size + sizeof(t_block);
  data = get_data();
  if ((data->start_heap == NULL || data->brk == NULL) &&
      init_heap_data() < 0)
    return (NULL);
  if (data->mem_left < length)
    return (NULL);
  bl = data->brk - data->mem_left;
  bl->next_size = NULL;
  bl->size = size;
  bl->free = 0;
  data->mem_left -= length;
  return (bl);
}
