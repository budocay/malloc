/*
** free for PSU_2019_malloc
**
** Made by pirou_g in /home/pirou_g/piscine_tek2/PSU_2019_malloc
** Login   <pirou_g@epitech.net>
**
** Started on     25/01/16 22:38
** Last update on 25/01/16 22:38
*/

#include <stdio.h>
#include "my_malloc.h"

void    free(void *ptr)
{
    fprintf(stdout, "free\n");
    add_block(ptr);
}