# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 12:53:19 by arahmoun          #+#    #+#              #
#    Updated: 2023/12/09 14:39:53 by arahmoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 

PSRC = parser/*.c

RSRC = raycasting/*.c
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
