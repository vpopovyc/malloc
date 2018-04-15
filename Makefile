# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/09 16:17:58 by vpopovyc          #+#    #+#              #
#    Updated: 2018/04/09 16:18:00 by vpopovyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SHARED = libft_malloc_${HOSTTYPE}.so

SYMLINK = libft_malloc.so

CORE = src/free.c src/globals.c src/malloc.c src/page.c \
		src/realloc.c src/show_alloc_mem.c

SRC += $(CORE)

OBJ = $(SRC:.c=.o)

CC = clang

MALLOCINC = -I. -Isrc

CCFLAGS = -Wall -Wextra -Werror
SHAREDFLAGS = -Wall -Wextra -Werror -shared

# **************************************************************************** #

LIBFTBIN = libft/libft.a

LIBFTINC = libft/includes

LIBFT = libft

# **************************************************************************** #

LIBS = -lft

LIBSDIR = -L$(LIBFT)

LIBSINC = -I$(LIBFTINC)

# **************************************************************************** #

all: $(SHARED) $(SYMLINK)

$(SHARED): $(LIBFTBIN) $(OBJ)
	$(CC) $(SHAREDFLAGS) $(MALLOCINC) $(LIBSDIR) $(LIBS) $(OBJ) -o $(SHARED)

$(SYMLINK):
	@ln -s $(SHARED) $(SYMLINK)

$(LIBFTBIN): libft.all

%.o: %.c
	$(CC) $(CCFLAGS) $(LIBSINC) $(MALLOCINC) -o $@ -c $<

norm:
	@norminette $(CORE) src/page.h malloc.h

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(SYMLINK)
	@rm -rf $(SHARED)

re: fclean all

libft.all:
	@echo  "\x1b[32mlibft   compiles...\x1b[0m"
	@make -C libft/ all

libft.clean:
	@make -C libft/ clean

libft.fclean:
	@make -C libft/ fclean

libft.re:
	@make -C libft/ re
