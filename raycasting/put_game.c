/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 09:48:30 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/21 15:29:34 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
int	ft_exit(int key, t_game *game)
{
	(void)game;
	exit(0);
	return (key);
}

int	key_hook(int key, t_game *game)
{
	printf("%d\n", key);
// moves
	if (key == 13)
		ft_up(game);
	if (key == 1)
		ft_down(game);
	// if (key == 2)
	// 	ft_right(game);
	// if (key == 0)
	// 	ft_lift(game);

// rotation
	if (key == 124)
		ft_rotat_right(game);
	if (key == 123)
		ft_rotat_lift(game);

// exit
	if (key == 53)
	{
		printf("%s ______ YOU EXIT THE GAME _____ %s", "\033[7m\033[33m",
			"\033[0m");
		exit(0);
	}
	return (key);
}

void	put_player(t_game *game)
{
    printf("put player in\nx : %d\ny : %d\n", game->xplayer, game->yplayer);

	mlx_pixel_put(game->mlx, game->win, game->xplayer - 1, game->yplayer - 1, 16711680);
	mlx_pixel_put(game->mlx, game->win, game->xplayer , game->yplayer - 1, 16711680);
	mlx_pixel_put(game->mlx, game->win, game->xplayer + 1, game->yplayer - 1, 16711680);

	mlx_pixel_put(game->mlx, game->win, game->xplayer - 1, game->yplayer, 16711680);
	mlx_pixel_put(game->mlx, game->win, game->xplayer , game->yplayer, 16711680);
	mlx_pixel_put(game->mlx, game->win, game->xplayer + 1, game->yplayer, 16711680);

	mlx_pixel_put(game->mlx, game->win, game->xplayer - 1, game->yplayer + 1, 16711680);
	mlx_pixel_put(game->mlx, game->win, game->xplayer , game->yplayer + 1, 16711680);
	mlx_pixel_put(game->mlx, game->win, game->xplayer + 1, game->yplayer + 1, 16711680);
}

void draw_grid(t_game *game, t_map *map)
{
	int x;
	int y;
	int j = -1;

	y = 0;
	while (y < ft_wc_l(map->maps) * 32)
	{
		x = 0;
		if (y % 32 == 0)
			j++;
		while (x < ft_len(map->maps[j]) * 32)
		{
			if(x % 32 == 0  || y % 32 == 0)
				mlx_pixel_put(game->mlx, game->win, x, y, 5308240);
			x++;
		}
		y++;
	}
}

void	mlx_put_squar(t_game *game, int color)
{
	// printf("[  width = %d  hight = %d  color = %d ] \n", game->width, game->hight, color);
	int w = game->width;
	while(game->hight < game->size * (game->y + 1))
	{
		game->width = w;
		while(game->width < game->size * (game->x + 1))
		{
			mlx_pixel_put(game->mlx, game->win, game->width, game->hight, color);
			game->width++;
		}
		game->hight++;
	}
}

void put_ground(t_game *game, t_map *map)
{
	int h;

	game->y = 0;
	game->hight = 0;
	while(map->maps[game->y])
	{
		game->x = 0;
		game->width = 0;
		h = game->hight;
		while(map->maps[game->y][game->x])
		{
			if(map->maps[game->y][game->x] == '0' || map->maps[game->y][game->x] == map->player)
				mlx_put_squar(game, 64682174);
			else
			{
				game->width +=32;
				game->hight +=32;
			}
			game->x++;
			game->hight = h;
		}
		game->hight += 32;
		game->y++;
	}
}

void    put_game(t_game *game, t_map *map)
{	
	int h;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1600, 1080, (char *)" cub ");

	// put pixel
	game->t_map = map;
	game->size = 32;
	put_ground(game, map);
	game->hight = 0;
	game->y = 0;
	while(map->maps[game->y])
	{
		game->x = 0;
		game->width = 0;
		h = game->hight;
		while(map->maps[game->y][game->x])
		{
			if(map->maps[game->y][game->x] == '1')
				mlx_put_squar(game, 255);
			else if(map->maps[game->y][game->x] == map->player)
			{
				mlx_put_squar(game, 64682174);
				game->xplayer = (game->width - (game->size/ 2));
				game->yplayer = (game->hight - (game->size/ 2));
				put_player(game);
			}
			else
			{
				game->width +=32;
				game->hight +=32;
			}
			game->x++;
			game->hight = h;
		}
		game->hight += 32;
		game->y++;
	}
	draw_grid(game, map);
	game->rotatangle = M_PI / 2;
	shut_rays(game, map);
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 17, 1L << 0, ft_exit, game);
	mlx_loop(game->mlx);
}