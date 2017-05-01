# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/11 17:23:23 by liabanzh          #+#    #+#              #
#    Updated: 2017/02/11 17:23:25 by liabanzh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
GCC 	= gcc
WWW		= -Wall -Wextra -Werror
SRC     = draw_line.c draw_map.c main.c math.c on_hook.c dop.c
OBJ     = $(SRC:.c=.o)
LIBFT   = ./libft/libft.a
LIBINC  = -I./libft
LIBLINK = -L./libft -lft
SRCS    = ./src/
INC     = ./includes/
IGRAPH  = -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL \
			-framework AppKit

all: libft $(NAME)

%.o:$(SRCS)%.c
	$(GCC) $(WWW) $(LIBINC) -I $(INC) -o $@ -c $<

libft: $(LIBFT)

$(LIBFT):
	make -C ./libft

$(NAME): $(OBJ)
	$(GCC) $(WWW) $(IGRAPH) $(LIBLINK) -o $(NAME) $(OBJ)

clean: cleanlibft
	rm -rf $(OBJ)

cleanlibft:
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME) $(LIBFT)

re: fclean all
