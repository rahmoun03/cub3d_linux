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

void    print_wall(t_game *game, int color)
{
    int top = (HEIGHT / 2) - game->projectedWallHeight / 2;
    int bottom = top + game->projectedWallHeight;
    game->y = top;
    while (game->y <= bottom)
    {
        my_mlx_pixel_put(game, game->x, game->y, color);
        game->y++;
    }
}


void    shut_rays(t_game *game, t_map *map)
{
    int pix ;
    int i = (WIDTH / 2) * -1;
    game->x = 0;
    double rayangle = -PI / 6;
    while (rayangle <= PI / 6 && game->x < WIDTH)
    {
        pix = 0;
        while(map->maps[(int)(game->yplayer + sin(game->rotatangle + rayangle) * pix) / SIZE]
            [(int)(game->xplayer + cos(game->rotatangle + rayangle) * pix) / SIZE] != '1')
        {
            my_mlx_pixel_put(game, ((game->xplayer) + cos(game->rotatangle + rayangle) * pix),
            (game->yplayer + sin(game->rotatangle + rayangle) * pix), 16711680);
            pix++;
        }
        i++;
        rayangle += game->rotatspeed;
        game->x++;
    }
}

void   render_3d(t_game *game, t_map *map)
{
	game->distance = 0;
	int pix ;
	int i = (WIDTH / 2) * -1;
	double rayangle = (-1 * PI) / 6;
	game->x = 0;

	while (rayangle <= PI / 6 && game->x < WIDTH)
	{
		pix = 0;
		while(map->maps[(int)((game->yplayer + (sin(game->rotatangle + (rayangle)) * pix)) / SIZE)]
			[(int)((game->xplayer + (cos(game->rotatangle + (rayangle)) * pix)) / SIZE) ] != '1')
		{
			pix++;
		}
		game->distance = pix;
		double angle = fabs(rayangle);
		if ((rayangle) < PI / 2)
			game->new_distance = game->distance * cos(angle);
		else
			game->new_distance = game->distance * cos(PI - (angle));
		game->distance = game->new_distance;
		game->projectedWallHeight = (SIZE * WIDTH) / game->distance;
		print_wall(game, 16711680);
		
		i++;
		rayangle += game->rotatspeed;
		game->x++;
	}
}