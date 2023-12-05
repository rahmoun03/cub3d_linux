#include "../cub.h"

void    black_screen(t_game *game)
{
    int x = 0;
    int y = 0;
    while (y <= HEIGHT)
    {
        x = 0;
        while (x <= WIDTH)
        {
            my_mlx_pixel_put(game, x, y, 0);
            x++;
        }
        y++;
    }
}

// rgb = 65536 * r + 256 * g + b;

void    print_wall(t_game *game, int color)
{
    int ceiling = (game->t_map->ceiling.r * 65536) + (game->t_map->ceiling.g * 256) + game->t_map->ceiling.b;
    int floor = (game->t_map->floor.r * 65536) + (game->t_map->floor.g * 256) + game->t_map->floor.b;
    int top = (HEIGHT / 2) - game->projectedWallHeight / 2;
    int bottom = top + game->projectedWallHeight;
    game->y = 0;
    while (game->y < top)
    {
        my_mlx_pixel_put(game, game->x, game->y, ceiling);
        game->y++;
    }
    while (game->y <= bottom)
    {
        my_mlx_pixel_put(game, game->x, game->y, color);
        game->y++;
    }
    while (game->y < HEIGHT)
    {
        my_mlx_pixel_put(game, game->x, game->y, floor);
        game->y++;
    }
    
}


int check_rays_2D(t_game *game, t_map *map, int pix, double x, double y)
{
	if(map->maps[(int)((y + (sin(game->rotatangle + game->rayangle) * pix)) - 1) / 10]
        [(int)(x + (cos(game->rotatangle + game->rayangle) * pix)) / 10] == '1')
		return 0;
	else if(map->maps[(int)((y + (sin(game->rotatangle + game->rayangle) * pix)) + 1) / 10]
		[(int)(x + (cos(game->rotatangle + game->rayangle) * pix)) / 10] == '1')
		return 0;
	else if(map->maps[(int)((y + (sin(game->rotatangle + game->rayangle) * pix))) / 10]
		[(int)((x + (cos(game->rotatangle + game->rayangle) * pix)) + 1) / 10] == '1')
		return 0;
	else if(map->maps[(int)((y + (sin(game->rotatangle + game->rayangle) * pix))) / 10]
		[(int)((x + (cos(game->rotatangle + game->rayangle) * pix)) - 1) / 10] == '1')
		return 0;
	return (1);
}

int check_rays_3D(t_game *game, t_map *map, int pix)
{
	if(map->maps[(int)((game->yplayer + (sin(game->rotatangle + game->rayangle) * pix)) - 1) / SIZE]
        [(int)(game->xplayer + (cos(game->rotatangle + game->rayangle) * pix)) / SIZE] == '1')
		return 0;
	else if(map->maps[(int)((game->yplayer + (sin(game->rotatangle + game->rayangle) * pix)) + 1) / SIZE]
		[(int)(game->xplayer + (cos(game->rotatangle + game->rayangle) * pix)) / SIZE] == '1')
		return 0;
	else if(map->maps[(int)((game->yplayer + (sin(game->rotatangle + game->rayangle) * pix))) / SIZE]
		[(int)((game->xplayer + (cos(game->rotatangle + game->rayangle) * pix)) + 1) / SIZE] == '1')
		return 0;
	else if(map->maps[(int)((game->yplayer + (sin(game->rotatangle + game->rayangle) * pix))) / SIZE]
		[(int)((game->xplayer + (cos(game->rotatangle + game->rayangle) * pix)) - 1) / SIZE] == '1')
		return 0;
	return (1);
}


void    shut_rays(t_game *game, t_map *map)
{
    int color;
    double x = ((double)game->xplayer / SIZE) * 10;
    double xp = MINI_WIDTH / 2;
    double yp = MINI_HEIGHT / 2;
    double y = ((double)game->yplayer / SIZE) * 10;
    double pix ;
    game->x = 0;
    game->rayangle = -PI / 6;
    while (game->rayangle <= PI / 6 && game->x < WIDTH)
    {
        pix = 0.0;
        color = 15790080;
        while(pix <= 50 && check_rays_2D(game, map, pix, x, y))
        {
            my_mlx_pixel_put(game, (xp + (cos(game->rotatangle + game->rayangle) * pix)),
            (yp + (sin(game->rotatangle + game->rayangle) * pix)), color);
            pix++;
        }
        game->rayangle += game->rotatspeed;
        game->x++;
    }
}

void   render_3d(t_game *game, t_map *map)
{
	game->distance = 0;
	double pix ;
    game->rayangle = (-1 * PI) / 6;
	game->x = 0;

	while (game->rayangle <= PI / 6 && game->x < WIDTH)
	{
		pix = 0.0;
		while(check_rays_3D(game, map, pix))
		{
			pix++;
		}
		game->distance = pix;
		double angle = fabs(game->rayangle);
		if ((game->rayangle) < PI / 2)
			game->new_distance = game->distance * cos(angle);
		else
			game->new_distance = game->distance * cos(PI - (angle));
		game->distance = game->new_distance;
		game->projectedWallHeight = (SIZE * WIDTH) / game->distance;
		print_wall(game, 16711680);
		game->rayangle += game->rotatspeed;
		game->x++;
	}
}