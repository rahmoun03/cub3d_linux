/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:23:47 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/25 10:42:29 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void    print_lift_wall(t_game *game, int color)
{
    int fake_y;

    game->y = HEIGHT / 2;
    fake_y = 0;
    while (game->y >= 0 && fake_y <= (HEIGHT / 2) - game->distance)
    {
        my_mlx_pixel_put(game, game->x, game->y, color);
        fake_y++;
        game->y--;
    }
    fake_y = 0;
    game->y = HEIGHT / 2;
    while (game->y <= HEIGHT && fake_y <= (HEIGHT / 2) - game->distance )
    {
        my_mlx_pixel_put(game, game->x, game->y, color);
        fake_y++;
        game->y++;
    }
}

void    print_right_wall(t_game *game, int color)
{
    int fake_y;
    game->y = HEIGHT / 2;
    fake_y = 0;
    while (game->y >= 0 && fake_y <= (HEIGHT / 2) - game->distance)
    {
        my_mlx_pixel_put(game, game->x, game->y, color);
        fake_y++;
        game->y--;
    }
    fake_y = 0;
    game->y = HEIGHT / 2;
    while (game->y <= HEIGHT && fake_y <= (HEIGHT / 2) - game->distance)
    {
        my_mlx_pixel_put(game, game->x, game->y, color);
        fake_y++;
        game->y++;
    }
}


void    shut_rays(t_game *game, t_map *map)
{
    int pix ;
    int i = 0;

    while (i > (WIDTH / 2) * -1 && game->x >= 0)
    {
        pix = 0;
        while(map->maps[(int)(game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix) / SIZE]
            [(int)(game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix) / SIZE] != '1')
        {
            my_mlx_pixel_put(game, game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix,
            game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix, 16711680);
            pix++;
        }
        i--;
    }
    i = 0;
    while (i < (WIDTH / 2) * 1)
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
    }
}

void   render_3d(t_game *game, t_map *map)
{
    // int a;
    // int b;
    game->distance = 0;
    int pix ;
    int i = 0;
    game->x = WIDTH / 2;

    while (i >= (WIDTH / 2) * -1 && game->x >= 0)
    {
        pix = 0;
        while(map->maps[(int)(game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix) / SIZE]
            [(int)(game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix) / SIZE] != '1')
        {
            pix++;
        }
        // a = pow((int)(game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix) - game->yplayer, 2);
        // b = pow((int)(game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix) - game->xplayer, 2);
        game->distance = pix;
        game->distance = game->distance * cos(game->rotatangle * game->rotatspeed);
        print_lift_wall(game, 16711680);
        i--;
        game->x--;
    }
    i = 0;
    game->x = WIDTH / 2;
    while (i <= (WIDTH / 2) * 1)
    {
        pix = 0;
        while(map->maps[(int)(game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix) / SIZE]
            [(int)(game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix) / SIZE] != '1')
        {
            pix++;
        }
        // a = pow((int)(game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix) - game->yplayer, 2);
        // b = pow((int)(game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix) - game->xplayer, 2);
        game->distance = pix;
        game->distance = game->distance * cos(game->rotatangle * game->rotatspeed);
        print_right_wall(game, 16711680);
        i++;
        game->x++;
    }
}
