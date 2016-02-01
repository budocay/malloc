##
## Makefile for makefile in 
## 
## Made by lina_a
## Login   <lina_a@epitech.net>
## 
## Started on  Tue Jan 20 11:10:49 2015 lina_a
## Last update Tue Jan 20 11:10:49 2015 lina_a
##

CC	= gcc

RM	= rm -f

NAME	= malloc.so

CFLAGS	+= -Wall -Wextra -Werror -fPIC -shared
CFLAGS	+= -I ./src_alexis/include

SRCS	= ./src_alexis/malloc.c \
	  ./src_alexis/management_block.c \
	  ./src_alexis/calloc.c

OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(OBJS) $(CFLAGS) $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re clean fclean
