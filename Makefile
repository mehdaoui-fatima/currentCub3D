# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmehdaou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 16:49:15 by fmehdaou          #+#    #+#              #
#    Updated: 2019/12/30 12:18:21 by fmehdaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######### addddddd flags !!!!!!!!
NAME =	cub3d

LIBFT = ./libft/libft.a

CUB3D = cub3d.c

CUBLIB = cub3d.a

MLX = ./minilibx/libmlx.a

SRCS = initialize.c \
	   ./gnl/get_next_line.c \
	   ./gnl/get_next_line_utils.c \
	   parsing.c \
	   walls.c 
		
OBJS =$(SRCS:.c=.o)

FLAGS=-Wall -Werror -Wextra

CC=gcc

LIBS = -lz -framework OpenGL -framework AppKit -I mlx

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): ${OBJS}
		 @$(MAKE) -C ./libft
		 @ar rcs $(CUBLIB) $(OBJS)
		 @gcc -Wall -Werror -Wextra $(CUB3D) $(CUBLIB) $(LIBFT) $(MLX) $(LIBS) -o $(NAME) 

%.o : %.c
	@$(CC) -c -o $@ $< 
 
clean:
	@$(MAKE) -C ./libft clean
	@rm -f *.o
	@rm -f ./gnl/*.o
fclean: clean
	@$(MAKE) -C ./libft fclean
	#$(MAKE) -C ./minilibx fclean
	@rm -f $(NAME)
	@rm -f $(CUBLIB)
re: fclean all