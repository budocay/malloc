##
## Makefile for malloc in /home/pirou_g/PSU_2015_malloc/my_libc
## 
## Made by pirou_g
## Login   <pirou_g@epitech.net>
## 
## Started on  Fri Jan 29 09:56:02 2016 pirou_g
## Last update Fri Jan 29 09:56:25 2016 pirou_g
##


NAME		= libmy_malloc.so

CC		= gcc

CFLAGS		= -Wall -Wextra -shared -fPIC -I./include -I./my_libc/include -g

LDFLAGS		=

SRCS		= src/realloc.c \
		  src/free.c \
		  src/blocks.c \
		  src/malloc.c

OBJS		= $(SRCS:.c=.o)

TMPS		= $(SRCS:.c=c~) Makefile~ .gitignore~

RM		= rm -rf

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(SRCS) $(CFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJS) $(TMPS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
