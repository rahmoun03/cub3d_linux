/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:53:29 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/22 14:03:04 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./get_next_line/get_next_line.h"
# include "mlx.h"
# include <math.h>

# define RED "\033[7m\033[31m"
# define DEFFAULT "\033[0m"
# define GREEN "\033[7m\033[32m"
# define YOLLOW "\033[7m\033[33m"


# define WIDTH 1730
# define HEIGHT 1130

// data structer
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 								&img.endian);
// 	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// }
typedef struct s_ft
{
	int i;
	int j;
	int colum;
	int spaces;
	char **maps;
} t_ft;

typedef struct s_c
{
	char **numbers;
	int r;
	int g;
	int b;
}t_c;

typedef struct s_f
{
	char **numbers;
	int r;
	int g;
	int b;
}t_f;

typedef struct s_map
{
	int		j;
	int		a;
	int		i;
	int		spaces;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*f;
	char	*map;
	char	**maps;
	char	*dst;
	char	player;
	t_c		ceiling;
	t_f		floor;
}			t_map;

typedef struct s_game
{
	int		size;
	int		xplayer;
	int		yplayer;
	int		x;
	int		y;
	float	rotatangle;
	float	rotatspeed;
	int		movespeed;
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
int		ft_atoi(char *str);
int		ft_is_digit(int c);
void	check_element(t_map *map);
void	check_map(t_map *map);
void	check_c_f(t_map *map);
void 	map_closed(t_map *map);
void	flood_fill(t_ft *tmp, int i, int j);
int	ft_len(char *str);
int	ft_wc_l(char **str);



void    put_game(t_game *game, t_map *map);
void    shut_rays(t_game *game, t_map *map);
void    direction(t_game *game, t_map *map);
void	put_player(t_game *game);
void	mlx_put_squar(t_game *game, int color);
void    ft_up(t_game *game);
void	draw_grid(t_game *game, t_map *map);

// moves
void    ft_up(t_game *game);
void    ft_down(t_game *game);
void    ft_right(t_game *game);
void    ft_lift(t_game *game);
void 	put_ground(t_game *game, t_map *map);
void    ft_rotat_right(t_game *game);
void    ft_rotat_lift(t_game *game);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
# endif