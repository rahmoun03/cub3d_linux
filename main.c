/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 12:53:22 by arahmoun          #+#    #+#             */
/*   Updated: 2023/08/01 13:37:34 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	key_h(int key, t_game *game)
{
	if (key == 126 || key == 13)
		ft_up(game, game->t_map);
	// if (key == 125 || key == 1)
	// 	ft_down(game);
	// if (key == 124 || key == 2)
	// 	ft_right(game);
	// if (key == 123 || key == 0)
	// 	ft_lift(game);
	if (key == 53)
	{
		printf("%s ______ YOU EXIT THE GAME _____ %s", "\033[7m\033[33m",
			"\033[0m");
		exit(0);
	}
	return (key);
}

int	check_path(char *str)
{
	int		i;
	int		j;
	char	*ber;

	j = 0;
	ber = ft_strdup(".ber");
	i = ft_strlen(str) - 4;
	while (str[i])
	{
		if (str[i] != ber[j])
		{
			free(ber);
			return (0);
		}
		i++;
		j++;
	}
	if (!str[i] && !ber[j])
	{
		free(ber);
		return (1);
	}
	free(ber);
	return (0);
}

void	put_image(t_game *game, char *filename)
{
	game->xpm = mlx_xpm_file_to_image(game->mlx, filename, &game->width,
			&game->hight);
	mlx_put_image_to_window(game->mlx, game->win, game->xpm, game->x, game->y);
	mlx_destroy_image(game->mlx, game->xpm);
}

void	put_player(t_game *game)
{
	int x = game->x;
	int y = game->y;
	int i = 0;
	while (i < 3)
	{
		int j = 0;
		y = game->y;
		while (j < 3)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, 16711680);
			j++;
			y++;
		}
		i++;
		x++;
	}	
}

void	ground(t_game *game, t_map *ptr)
{
	game->y = 0;
	int y = 6;
	int x;
	while (ptr->maps[y])
	{
		game->x = 0;
		x = 0;
		while (ptr->maps[y][x])
		{
			if(ptr->maps[y][x] == '0' || (ptr->maps[y][x] != '1' && ptr->maps[y][x] != ' '))
			{
				put_image(game, ptr->we);
				if(ptr->maps[y][x] == 'N')
					put_player(game);
				game->x += 10;
				x++;
			}
			else if(ptr->maps[y][x] == '1')
			{
				put_image(game, ptr->so);
				game->x += 10;
				x++;
			}
			else
			{
				game->x += 10;
				x++;
			}
		}
		game->y += 10;
		y++;
	}
}

int	main(int ac, char **av)
{
	int		fd;
	t_map	*ptr;
	t_game	*game;

	ptr = (t_map *)malloc(sizeof(t_map));
	game = (t_game *)malloc(sizeof(t_game));
	fd = open(av[1], O_RDWR);
	if (ac != 2 || fd == -1 || !check_path(av[1]))
	{
		printf(" %sinvalid path\n%s ", RED, DEFFAULT);
		return (0);
	}
    else
	{
        printf("%s valid \n%s" , GREEN, DEFFAULT);
		read_file(ptr, fd);
		check_element(ptr);
		printf("\n\n\n\n\n%s\n", ptr->no);
		printf("\n%s\n", ptr->so);
		printf("\n%s\n", ptr->we);
		printf("\n%s\n", ptr->ea);
		printf("\n%s\n", ptr->f);
		printf("\n%s\n\n\n\n\n", ptr->c);
		game->mlx = mlx_init();
		game->width = 1920;
		game->hight = 1080;
		game->win = mlx_new_window(game->mlx, game->width, game->hight, "cub3D");
		ground(game, ptr);
		mlx_hook(game->win, 2, 1L << 0, key_h, game);
		mlx_loop(game->mlx);
	}
}


