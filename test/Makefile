CC	= gcc

CFLAGS	= -Wall -Wextra -fPIC

LDFLAGS	= -shared

SRCS	= malloc.c

OBJS	= $(SRCS:.c=.o)

BIN	= libtest.so

RM	= rm -rf

all:	$(BIN)

$(BIN):	$(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BIN)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(BIN)

re:	fclean all

.PHONY:	all clean fclean rex
