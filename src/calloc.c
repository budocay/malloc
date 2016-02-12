/*
** calloc.c for calloc in
**
** Made by lina_a
** Login   <lina_a@epitech.net>
**
** Started on  Mon Feb  1 08:28:14 2016 lina_a
** Last update Mon Feb  1 08:28:14 2016 lina_a
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "malloc.h"

void*     calloc(size_t size1, size_t size2)
{
    size_t  size;
    void*   ptr;

    size = size1 * size2;
    if (size < (size1 * size2))
        return (NULL);
    if ((ptr = malloc(size)) == NULL)
        return (NULL);
    memset(ptr, 0, size);
    return (ptr);
}