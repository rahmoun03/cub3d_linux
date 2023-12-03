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


void    shut_rays(t_game *game, t_map *map)
{
    float x = ((float)game->xplayer / SIZE) * 10;
    float y = ((float)game->yplayer / SIZE) * 10;
    int pix ;
    int i = (WIDTH / 2) * -1;
    game->x = 0;
    game->rayangle = -PI / 6;
    while (game->rayangle <= PI / 6 && game->x < WIDTH)
    {
        pix = 0;
        while(map->maps[(int)(y + (sin(game->rotatangle + game->rayangle) * pix)) / 10]
            [(int)(x + (cos(game->rotatangle + game->rayangle) * pix)) / 10] != '1')
        {
            my_mlx_pixel_put(game, (x + cos(game->rotatangle + game->rayangle) * pix),
            (y + (sin(game->rotatangle + game->rayangle) * pix)), 16711680);
            pix++;
        }
        i++;
        game->rayangle += game->rotatspeed;
        game->x++;
    }
}

void   render_3d(t_game *game, t_map *map)
{
	game->distance = 0;
	int pix ;
	int i = (WIDTH / 2) * -1;
    game->rayangle = (-1 * PI) / 6;
	game->x = 0;

	while (game->rayangle <= PI / 6 && game->x < WIDTH)
	{
		pix = 0;
		while(map->maps[(int)((game->yplayer + (sin(game->rotatangle + (game->rayangle)) * pix)) / SIZE)]
			[(int)((game->xplayer + (cos(game->rotatangle + (game->rayangle)) * pix)) / SIZE) ] != '1')
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
		
		i++;
		game->rayangle += game->rotatspeed;
		game->x++;
	}
}