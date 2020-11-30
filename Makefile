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

NAME =	cub3d

LIBFT = ./libft/libft.a

CUB3D = src/cub3d.c

CUBLIB = src/cub3d.a

MLX = minilibx/libmlx.a

SRCS =  gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		src/walls/initialize.c \
		src/parsing/parsing.c \
		src/parsing/parse_resolution.c \
		src/parsing/parse_utils.c \
		src/parsing/parse_ceil_floor.c \
		src/parsing/parse_texture.c \
		src/parsing/parse_map.c \
		src/parsing/map_check.c \
		src/parsing/map_create.c \
		src/sprites/sprite.c \
		src/walls/movement.c \
		src/walls/draw1.c \
		src/walls/draw2.c \
		src/walls/walls.c \
		bmpfile/make_bmp.c

		
OBJS =$(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror 

LIBS = -lz -framework OpenGL -framework AppKit -I mlx

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): ${OBJS}
		 @$(MAKE) -C ./libft
		 @ar rcs $(CUBLIB) $(OBJS)
		 gcc $(FLAGS) $(CUB3D) $(CUBLIB) $(LIBFT) $(MLX) $(LIBS) -o $(NAME) 

%.o : %.c
	@$(CC) -c -o $@ $< 
 
clean:
	@$(MAKE) -C ./libft clean
	@rm -f ${OBJS}





	
fclean: clean
	@$(MAKE) -C ./libft fclean
	@rm -f $(NAME)
	@rm -f $(CUBLIB)
re: fclean all