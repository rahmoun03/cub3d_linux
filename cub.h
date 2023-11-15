/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:53:29 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/15 01:05:35 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "/home/arahmoun/Desktop/minilibx-linux/mlx.h"
# include "/home/arahmoun/Desktop/minilibx-linux/mlx_int.h"
# include "./get_next_line/get_next_line.h"

# define RED "\033[7m\033[31m"
# define DEFFAULT "\033[0m"
# define GREEN "\033[7m\033[32m"
# define YOLLOW "\033[7m\033[33m"

// data structer

typedef struct s_map
{
	int		j;
	int		a;
	int		i;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*f;
	char	*map;
	char	**maps;
	char	*dst;
}			t_map;

typedef struct s_game
{
	int		start;
	int		xlpayer;
	int		ylpayer;
	int		x;
	int		y;
	void	*img;
	void	*win;
	void	*mlx;
	void	*xpm;
	int		hight;
	int		chight;
	int		width;
	int		cwidth;
	char	**map;
	t_map	*t_map;
}			t_game;

// functions

void    read_file(t_map *map, int fd);
char	**ft_split(char const *s, char c);
void	check_element(t_map *map);


void	ft_up(t_game *game, t_map *ptr);
void	put_player(t_game *game);
void	put_image(t_game *game, char *filename);

// void	ft_down(t_game *game);
// void	ft_right(t_game *game);
// void	ft_lift(t_game *game);


# endif