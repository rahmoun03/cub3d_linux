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

    game->y = (HEIGHT / 2) - (game->new_distance / 2);
    while (game->y <  (HEIGHT / 2) + (game->new_distance / 2))
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
    while (game->x < WIDTH )
    {
        pix = 0;
        while(map->maps[(int)(game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix) / SIZE]
            [(int)(game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix) / SIZE] != '1')
        {
            my_mlx_pixel_put(game, game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix,
            game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix, 16711680);
            pix++;
        }
        i++;
        game->x++;
    }
}

void   render_3d(t_game *game, t_map *map)
{
    double xwall;
    double ywall;
    game->distance = 0;
    int pix ;
    int i = (WIDTH / 2) * -1;
    game->x = 0;

    while (game->x < WIDTH)
    {
        pix = 0;
        while(map->maps[(int)(game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix) / SIZE]
            [(int)(game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix) / SIZE] != '1')
        {
            pix++;
        }
        ywall = pow((game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix) - game->yplayer, 2);
        xwall = pow((game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix) - game->xplayer, 2);
        game->distance = sqrt(xwall + ywall);
        game->new_distance = (WIDTH / 2) / tan(game->rotatangle + i * game->rotatspeed / 2);
        game->projectedWallHeight = (SIZE / game->distance) * game->new_distance;
        printf("old    =    %f\n", game->distance);
        printf("new    =    %f\n", game->new_distance);
        printf("wall    =    %f\n", game->projectedWallHeight);
        print_wall(game, 16711680);
        
        // exit(0);
        i++;
        game->x++;
    }
}