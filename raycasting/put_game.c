/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 09:48:30 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/20 15:45:41 by arahmoun         ###   ########.fr       */
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

	(void)game;
	printf("%d\n", key);
	// if (key == 126 || key == 13)
	// 	ft_up(game);
	// if (key == 125 || key == 1)
	// 	ft_down(game);
	// if (key == 124 || key == 2)
	// 	ft_right(game);
	// if (key == 123 || key == 0)
	// 	ft_lift(game);
	// if (key == 53)
	// {
	// 	ft_printf("%s ______ YOU EXIT THE GAME _____ %s", "\033[7m\033[33m",
	// 		"\033[0m");
	// 	exit(0);
	// }
	// if (key == 36 && game->start <= 1)
	// {
	// 	if (game->start == 1)
	// 		exit(0);
	// 	game->start = 3;
	// 	ground(game);
	// 	draw_map(game);
	// }
	return (key);
}

void	put_player(t_game *game)
{
	int i;
	int j;

	printf("put _ player \n");
	i = 0;
	while(i < 3)
	{
		j = 0;
		while (j < 3)
		{
			mlx_pixel_put(game->mlx, game->win, game->width + j, game->hight + i, 16711680);
			j++;
		}
		i++;
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
void    put_game(t_game *game, t_map *map)
{
	(void)map;
	
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1600, 1080, (char *)" cub ");

	// put pixel
	game->y = 0;
	game->hight = 0;
	int h;
	game->size = 32; 
	while(map->maps[game->y])
	{
		game->x = 0;
		game->width = 0;
		h = game->hight;
		while(map->maps[game->y][game->x])
		{
			if(map->maps[game->y][game->x] == '0')
				mlx_put_squar(game, 64682174);
			else if(map->maps[game->y][game->x] == '1')
				mlx_put_squar(game, 255);
			else if(map->maps[game->y][game->x] == map->player)
			{
				mlx_put_squar(game, 64682174);
				put_player(game);
			}
			else
				mlx_put_squar(game, 0);
			game->x++;
			game->hight = h;
		}
		game->hight += 32;
		game->y++;
	}

	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 17, 1L << 0, ft_exit, game);
	mlx_loop(game->mlx);
}