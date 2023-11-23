/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 09:48:30 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/23 17:27:30 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
void	draw_start(t_game *game);
int	ft_exit(int key, t_game *game)
{
	if(game->win)
		exit(0);
	return (key);
}

int	key_hook(int key, t_game *game)
{
	printf("%d\n", key);
	// (void)game;
// moves
	if (key == UP)
		ft_up(game);
	else if (key == DOWN)
		ft_down(game);
	// if (key == 2)
	// 	ft_right(game);
	// if (key == 0)
	// 	ft_lift(game);
	else if(key == ENTER)
		draw_start(game);

// rotation
	if (key == 124)
		ft_rotat_right(game);
	if (key == 123)
		ft_rotat_lift(game);

// exit
	if (key == ESC)
	{
		printf("%s ______ YOU EXIT THE GAME _____ %s", "\033[7m\033[33m",
			"\033[0m");
		exit(0);
	}
	return (key);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	put_player(t_game *game)
{
    // printf("put player in\nx : %d\ny : %d\n", game->xplayer, game->yplayer);

	my_mlx_pixel_put(game, game->xplayer - 1, game->yplayer - 1, 16711680);
	my_mlx_pixel_put(game, game->xplayer , game->yplayer - 1, 16711680);
	my_mlx_pixel_put(game, game->xplayer + 1, game->yplayer - 1, 16711680);

	my_mlx_pixel_put(game, game->xplayer - 1, game->yplayer, 16711680);
	my_mlx_pixel_put(game, game->xplayer , game->yplayer, 16711680);
	my_mlx_pixel_put(game, game->xplayer + 1, game->yplayer, 16711680);

	my_mlx_pixel_put(game, game->xplayer - 1, game->yplayer + 1, 16711680);
	my_mlx_pixel_put(game, game->xplayer , game->yplayer + 1, 16711680);
	my_mlx_pixel_put(game, game->xplayer + 1, game->yplayer + 1, 16711680);
}

void draw_grid(t_game *game, t_map *map)
{
	int x;
	int y;
	int j = -1;

	y = 0;
	while (y < ft_wc_l(map->maps) * SIZE)
	{
		x = 0;
		if (y % SIZE == 0)
			j++;
		while (x < ft_len(map->maps[j]) * SIZE)
		{
			if(x % SIZE == 0  || y % SIZE == 0)
				my_mlx_pixel_put(game, x, y, 5308240);
			x++;
		}
		y++;
	}
}

void	mlx_put_squar(t_game *game, int color)
{
	// printf("[  width = %d  hight = %d  color = %d ] \n", game->width, game->hight, color);
	int w = game->width;
	while(game->hight < SIZE * (game->y + 1))
	{
		game->width = w;
		while(game->width < SIZE * (game->x + 1))
		{
			my_mlx_pixel_put(game, game->width, game->hight, color);
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
				game->width += SIZE;
				game->hight += SIZE;
			}
			game->x++;
			game->hight = h;
		}
		game->hight += SIZE;
		game->y++;
	}
}

void 	init_rotation(t_game *game, t_map *map)
{
	if (map->player == 'N')
		game->rotatangle =  180;
	else if (map->player == 'E')
		game->rotatangle = 270;
	else if (map->player == 'S')
		game->rotatangle = 360;
	else if (map->player == 'W')
		game->rotatangle = 90;

	game->rotatspeed = 4 * (M_PI / 360);
}

void	put_image(t_game *game, char *filename)
{
	game->xpm = mlx_xpm_file_to_image(game->mlx, filename, &game->width,
			&game->hight);
	mlx_put_image_to_window(game->mlx, game->win, game->xpm, 0, 0);
	mlx_destroy_image(game->mlx, game->xpm);
}



void	draw_start(t_game *game)
{
	// sleep(5);
	put_image(game, "texture/ps1.xpm");
	// sleep(1);
	put_image(game, "texture/ps2.xpm");
	// sleep(1);
	put_image(game, "texture/ps3.xpm");
	// sleep(1);
	put_image(game, "texture/ps4.xpm");
	// sleep(1);
	put_image(game, "texture/ps5.xpm");
	// sleep(5);
}

void	player_pos(t_game *game, t_map *map)
{
	int y;
	int x;

	y = 0;
	while (map->maps[y])
	{
		x = 0;
		while (map->maps[y][x])
		{
			if(map->maps[y][x] == map->player)
			{
				map->maps[y][x] = '0';
				game->xplayer = ((x + 1) * SIZE) - (SIZE / 2);
				game->yplayer = ((y + 1) * SIZE) - (SIZE / 2);
				return ;
			}
			x++;
		}
		y++;
	}
}


void    put_game(t_game *game, t_map *map)
{
	int h;
	

	// printf("{bpp = %d ,ll = %d   ,endian = %d   }\n", game->bits_per_pixel, game->line_length, game->endian);


	put_ground(game, game->t_map);
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
			else
			{
				game->width +=SIZE;
				game->hight +=SIZE;
			}
			game->x++;
			game->hight = h;
		}
		game->hight += SIZE;
		game->y++;
	}
	put_player(game);
	draw_grid(game, map);
	// shut_rays(game, game->t_map);
}

int update(t_game *game)
{
	put_game(game, game->t_map);


	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

void	start_mlx(t_game *game)
{
	/*  --------------------   start   -------------------------------*/ 
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, (char *)" cub ");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
	/*------------------------------------------------------------------------------------*/
	
	player_pos(game, game->t_map);
	init_rotation(game, game->t_map);
	
	/*  --------------------    end     ---------------------------- */
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 17, 1L << 0, ft_exit, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	/*------------------------------------------------------------------------------------*/
}
