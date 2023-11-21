# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 12:53:19 by arahmoun          #+#    #+#              #
#    Updated: 2023/11/21 09:32:30 by arahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 

PSRC = parser/utils.c parser/readfile.c parser/ft_split.c parser/ft_atoi.c

RSRC = raycasting/put_game.c raycasting/raycast.c raycasting/move_player.c

SRCS = ${GNL} ${PSRC} ${RSRC} main.c 

MLX = -lmlx -framework OpenGL -framework AppKit

MLX_LINUX = -lmlx -lXext -lX11 -lm -lmcheck

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

CC = cc ${FLAGS}


all: ${NAME}

${NAME}: ${SRCS}
	@${CC} ${SRCS} ${MLX} ${FLAGS} -o $@
	@tput setaf 2; echo "THE GAME IS READY"

clean:
	@rm -rf cub
	@tput setaf 1; echo "CLEAN COMPLET"

fclean: clean

re: clean all
