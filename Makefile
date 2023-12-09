# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 12:53:19 by arahmoun          #+#    #+#              #
#    Updated: 2023/12/09 17:41:12 by arahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 

PSRC = parser/ft_atoi.c   parser/readfile_continue2.c  parser/readfile_continue5.c  parser/readfile_continue.c \
		parser/ft_split.c  parser/readfile_continue3.c  parser/readfile_continue6.c  parser/utils.c \
		parser/readfile.c  parser/readfile_continue4.c  parser/readfile_continue7.c

RSRC = raycasting/raycast.c raycasting/raycast_2d.c raycasting/raycast_3d.c raycasting/put_game.c \
		raycasting/put_game2.c raycasting/put_game3.c raycasting/move_player.c \
		raycasting/minimap.c raycasting/init_game.c
		
SRCS = ${GNL} ${PSRC} ${RSRC} main.c 

MLX = -lmlx -framework OpenGL -framework AppKit

MLX_LINUX = -lmlx -lXext -lX11 -lm -lmcheck #-lbsd -lXext -lX11 -lm

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

CC = cc ${FLAGS}


all: ${NAME}

${NAME}: ${SRCS}
	@${CC} ${SRCS} ${MLX_LINUX} ${FLAGS} -o $@
	@tput setaf 2; echo "THE GAME IS READY"

clean:
	@rm -rf $(NAME)
	@tput setaf 1; echo "CLEAN COMPLET"

fclean: clean

re: clean all
