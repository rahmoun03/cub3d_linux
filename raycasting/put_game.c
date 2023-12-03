/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 09:48:30 by arahmoun          #+#    #+#             */
/*   Updated: 2023/12/03 18:16:10 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
		game->walkdirection = 1;
	else if (key == DOWN)
        game->walkdirection = -1;
	else if (key == RIGHT)
        game->walk_r_l = 1;
	else if (key == LIFT)
        game->walk_r_l = -1;
	else if(key == ENTER)
		game->start = 0;

// rotation
	else if (key == 65363)
    	game->rotaion = 1;
	else if (key == 65361)
   		game->rotaion = -1;

// exit
	else if (key == ESC)
	{
		printf("%s ______ YOU EXIT THE GAME _____ %s", "\033[7m\033[33m",
			"\033[0m");
		exit(0);
	}
	return (key);
}

int	release_key_hook(int key, t_game *game)
{
// moves
	if (key == UP)
		game->walkdirection = 0;
	else if (key == DOWN)
        game->walkdirection = 0;
	else if (key == RIGHT)
        game->walk_r_l = 0;
	else if (key == LIFT)
        game->walk_r_l = 0;


// rotation
	else if (key == 65363)
    	game->rotaion = 0;
	else if (key == 65361)
   		game->rotaion = 0;

	return (key);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && x <= WIDTH) && (y >= 0 && y <= HEIGHT))
	{
    // printf("put in\nx : %d\ny : %d\n", game->xplayer, game->yplayer);
		dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	put_player(t_game *game)
{
	float x = ((float)game->xplayer / SIZE) * 10;
	float y = ((float)game->yplayer / SIZE) * 10;
	my_mlx_pixel_put(game, x - 1, y - 1, 14549214);
	my_mlx_pixel_put(game, x - 1, y, 14549214);
	my_mlx_pixel_put(game, x - 1, y + 1, 14549214);
	
	my_mlx_pixel_put(game, x , y - 1, 14549214);
	my_mlx_pixel_put(game, x , y, 14549214);
	my_mlx_pixel_put(game, x , y + 1, 14549214);

	my_mlx_pixel_put(game, x + 1, y - 1, 14549214);
	my_mlx_pixel_put(game, x + 1, y, 14549214);
	my_mlx_pixel_put(game, x + 1, y + 1, 14549214);
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
	int w = game->width;
	while(game->hight < 10 * (game->y + 1))
	{
		game->width = w;
		while(game->width < 10 * (game->x + 1))
		{
			my_mlx_pixel_put(game, game->width, game->hight, color);
			game->width++;
		}
		game->hight++;
	}
}

void	calc_squar(t_game *game, int color)
{
	(void)color;
	int w = game->width;
	while(game->hight < SIZE * (game->y + 1))
	{
		game->width = w;
		while(game->width < SIZE * (game->x + 1))
		{
			// my_mlx_pixel_put(game, game->width, game->hight, color);
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
	while(map->maps[game->y] && game->hight < HEIGHT)
	{
		game->x = 0;
		game->width = 0;
		h = game->hight;
		while(map->maps[game->y][game->x] && game->width < WIDTH)
		{
			if(map->maps[game->y][game->x] == '0' || map->maps[game->y][game->x] == map->player)
				mlx_put_squar(game, 64682174);
			else
			{
				game->width += 10;
				game->hight += 10;
			}
			game->x++;
			game->hight = h;
		}
		game->hight += 10;
		game->y++;
	}
}

void 	init_rotation(t_game *game, t_map *map)
{
	if (map->player == 'N')
		game->rotatangle = 3 * PI / 2;
	else if (map->player == 'E')
		game->rotatangle = PI;
	else if (map->player == 'S')
		game->rotatangle = PI / 2;
	else if (map->player == 'W')
		game->rotatangle = 0;

	game->rotatspeed = (PI / 3) / WIDTH;
}

void	put_image(t_game *game, char *filename)
{
	game->xpm = mlx_xpm_file_to_image(game->mlx, filename, &game->width,
			&game->hight);
	// mlx_put_image_to_window(game->mlx, game->win, game->xpm, 0, 0);
	// mlx_destroy_image(game->mlx, game->xpm);
}
void init_animation(t_game *game)
{
	game->t_map->i = 0;
	game->t_map->j = 0;
	game->t_map->a = 0;
	game->t_map->l = 0;
	game->start = 1;
	
	const char *succes = "texture/start/01.xpm|texture/start/02.xpm|texture/start/03.xpm|texture/start/04.xpm|texture/start/05.xpm|texture/start/06.xpm|texture/start/07.xpm|texture/start/08.xpm|texture/start/09.xpm|texture/start/10.xpm|texture/start/11.xpm|texture/start/12.xpm|texture/start/13.xpm|texture/start/14.xpm|texture/start/15.xpm|texture/start/16.xpm|texture/start/17.xpm|texture/start/18.xpm|texture/start/19.xpm|texture/start/20.xpm|texture/start/21.xpm|texture/start/22.xpm|texture/start/23.xpm|texture/start/24.xpm|texture/start/25.xpm|texture/start/26.xpm|texture/start/27.xpm|texture/start/28.xpm|texture/start/29.xpm|texture/start/30.xpm|texture/start/31.xpm|texture/start/32.xpm|texture/start/33.xpm|texture/start/34.xpm|texture/start/35.xpm|texture/start/36.xpm|texture/start/37.xpm|texture/start/38.xpm|texture/start/39.xpm|texture/start/40.xpm|texture/start/41.xpm|texture/start/42.xpm|texture/start/43.xpm|texture/start/44.xpm|texture/start/45.xpm|texture/start/46.xpm|texture/start/47.xpm|texture/start/48.xpm|texture/start/49.xpm|texture/start/50.xpm|texture/start/51.xpm|texture/start/52.xpm|texture/start/53.xpm|texture/start/54.xpm|texture/start/55.xpm|texture/start/56.xpm|texture/start/57.xpm|texture/start/58.xpm|texture/start/59.xpm|texture/start/60.xpm|texture/start/61.xpm|texture/start/62.xpm|texture/start/63.xpm|texture/start/64.xpm|texture/start/65.xpm|texture/start/66.xpm|texture/start/67.xpm|texture/start/68.xpm|texture/start/69.xpm|texture/start/70.xpm|texture/start/71.xpm|texture/start/72.xpm|texture/start/73.xpm|texture/start/74.xpm|texture/start/75.xpm|texture/start/76.xpm|texture/start/77.xpm|texture/start/78.xpm|texture/start/79.xpm|texture/start/80.xpm|texture/start/81.xpm|texture/start/82.xpm|texture/start/83.xpm|texture/start/84.xpm|texture/start/85.xpm|texture/start/86.xpm|texture/succes/1.xpm|texture/succes/2.xpm|texture/succes/3.xpm|texture/succes/4.xpm|texture/succes/5.xpm|texture/succes/6.xpm|texture/succes/7.xpm|texture/succes/8.xpm";
	
	
	game->path = ft_split(succes, '|');
}


void	draw_start(t_game *game)
{
	if(game->t_map->a >= 0 && game->t_map->a <= 86)
	{
		if(game->t_map->l++ > 600)
		{
			put_image(game, game->path[game->t_map->a]);
			game->t_map->a++;
		}
	}
	else if(game->t_map->i >= 0 && game->t_map->i < 7)
	{
		if (game->t_map->l++ > 3000)
		{
			put_image(game, game->path[game->t_map->a + game->t_map->i]);
			game->t_map->i++;
		}
	}
	else
	{
		if(game->t_map->l++ > 6000)
		{
			game->start = 0;
		}
	}
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

void	check_moves(t_game *game)
{
	if(game->walkdirection == 1)
		ft_up(game);
	else if(game->walkdirection == -1)
		ft_down(game);

	if(game->walk_r_l == 1)
		ft_right(game);
	else if(game->walk_r_l == -1)
		ft_lift(game);
	
	if(game->rotaion == 1)
		ft_rotat_right(game);
	else if(game->rotaion == -1)
		ft_rotat_lift(game);
}

void	cub_3d(t_game *game)
{
	black_screen(game);
	render_3d(game, game->t_map);
}

void	cub_2d(t_game *game)
{
	int h;

	put_ground(game, game->t_map);
	game->hight = 0;
	game->y = 0;
	while(game->t_map->maps[game->y])
	{
		game->x = 0;
		game->width = 0;
		h = game->hight;
		while(game->t_map->maps[game->y][game->x])
		{
			if(game->t_map->maps[game->y][game->x] == '1')
				mlx_put_squar(game, 255);
			else
			{
				game->width +=10;
				game->hight +=10;
			}
			game->x++;
			game->hight = h;
		}
		game->hight += 10;
		game->y++;
	}
	put_player(game);
	// draw_grid(game, game->t_map);
	shut_rays(game, game->t_map);
}

void	mini_map(t_game *game)
{
	int x = ((float)game->xplayer / SIZE) * 10;
	int y = ((float)game->yplayer / SIZE) * 10;
	game->x = 10;
	game->y = 10;
	my_mlx_pixel_put(game, x, y, 255);

	while (game->y < MINI_HEIGHT)
	{
		game->x = 10;
		while (game->x < MINI_WIDTH)
		{
			my_mlx_pixel_put(game, x, y, 14142664);
			game->x++;
		}
		game->y++;
	}
}

int update(t_game *game)
{
	if(game->start)
	{
		draw_start(game);
		mlx_put_image_to_window(game->mlx, game->win, game->xpm, 0, 0);
		// mlx_destroy_image(game->mlx,game->xpm);
	}
	else
	{
		check_moves(game);
		cub_3d(game);
		// mini_map(game);
		cub_2d(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	}
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
	init_animation(game);
	put_image(game, game->path[0]);

	
	/*  --------------------    end     ---------------------------- */
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 3, 1L << 1, release_key_hook, game);
	mlx_hook(game->win, 17, 1L << 0, ft_exit, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	/*------------------------------------------------------------------------------------*/
}
