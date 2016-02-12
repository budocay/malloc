##
## Makefile for makefile in 
## 
## Made by lina_a
## Login   <lina_a@epitech.net>
## 
## Started on  Tue Jan 20 11:10:49 2015 lina_a
## Last update Tue Feb  2 17:54:37 2016 pirou_g
##

CC		= gcc

RM		= rm -f

NAME		= libmy_malloc.so

CFLAGS		= -Wall -Wextra -Werror -fPIC
CFLAGS		+= -I ./src/include

LDFLAGS		= -shared

SRCS		= ./src/malloc.c \
	  	  ./src/management_block.c \
	  	  ./src/calloc.c \
	  	  ./src/free.c \
		  ./src/realloc.c \
		  ./src/show_alloc_mem.c \
		  ./src/insert_blk.c

OBJS		= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re: 		fclean all

.PHONY: 	re clean fclean all
