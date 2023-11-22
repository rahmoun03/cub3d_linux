/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:23:47 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/22 12:44:38 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"
void    direction(t_game *game, t_map *map)
{
    game->chight = game->yplayer;
    game->cwidth = game->xplayer;

    if (map->player == 'N')
    {
        printf("\nN\n");
        while((game->chight)-- > 0 && map->maps[game->chight / game->size][game->cwidth / game->size] != '1')
            mlx_pixel_put(game->mlx, game->win, game->cwidth, game->chight, 16711680);
    }
    else if (map->player == 'E')
    {
        printf("\nE\n");
        while((game->cwidth)++ < ft_len(map->maps[game->chight / game->size]) * game->size && map->maps[game->chight / game->size][game->cwidth / game->size] != '1')
            mlx_pixel_put(game->mlx, game->win, game->cwidth, game->chight, 16711680);
    }
    else if (map->player == 'S')
    {
        printf("\nS\n");
        while((game->chight)++ < ft_wc_l(map->maps) * game->size && map->maps[game->chight / game->size][game->cwidth / game->size] != '1')
            mlx_pixel_put(game->mlx, game->win, game->cwidth, game->chight, 16711680);
    }
    else if (map->player == 'W')
    {
        printf("\nW\n");
        while((game->cwidth)-- > 0 && map->maps[game->chight / game->size][game->cwidth / game->size] != '1')
            mlx_pixel_put(game->mlx, game->win, game->cwidth, game->chight, 16711680);
    }
}
void    right_rays(t_game *game, t_map *map, int b)
{
    int x;
    int p;

    p = 0;
    x = 0;
    while((game->chight)-- > 0 && map->maps[game->chight / game->size][(game->cwidth + p) / game->size] != '1')
    {
        mlx_pixel_put(game->mlx, game->win, game->cwidth + p, game->chight, 16711680);
        if (x == b)
        {
            p++;
            x = 0;
        }
        x++;
    }    
}

void    lift_rays(t_game *game, t_map *map, int b)
{
    int x;
    int p;

    p = 0;
    x = 0;
    while((game->chight)-- > 0 && map->maps[game->chight / game->size][(game->cwidth - p) / game->size] != '1')
    {
        mlx_pixel_put(game->mlx, game->win, game->cwidth - p, game->chight, 16711680);
        if (x == b)
        {
            p++;
            x = 0;
        }
        x++;
    }
}

void    shut_rays(t_game *game, t_map *map)
{
    (void)map;
    int x ;
    int y ;
    int pix ;
    int i = 0;

    while (i < 360)
    {
        y = game->yplayer;
        x = game->xplayer;
        pix = 0;
        while(map->maps[(int)(y + sin(game->rotatangle + i * game->rotatspeed) * pix) / game->size][(int)(x + cos(game->rotatangle + i * game->rotatspeed) * pix) / game->size] != '1')
        {
            mlx_pixel_put(game->mlx, game->win, x + cos(game->rotatangle + i * game->rotatspeed) * pix, y + sin(game->rotatangle + i * game->rotatspeed) * pix, 16711680);
            pix++;
        }
        // game->rotatangle = M_PI / 2;
        //  game->rotatangle += 1 * game->rotatspeed;
        i++;
    }
    
    






    
    // int b;
    // int p;

    // b = 1;
    // p = 0;
    // direction(game, map);
    // game->chight = game->yplayer;
    // game->cwidth = game->xplayer;
    // if (map->player == 'N')
    // {
    //     while(b < game->size)
    //     {
    //         game->chight = game->yplayer;
    //         game->cwidth = game->xplayer;
    //         lift_rays(game, map, b);
    //         b++;
    //     }
    //     b = 1;
    //     while(b < game->size)
    //     {
    //         game->chight = game->yplayer;
    //         game->cwidth = game->xplayer;
    //         right_rays(game, map, b);
    //         b++;            
    //     }
    // }



    
    // if (map->player == 'E')
    // {        
    //     while(b < game->size)
    //     {
    //         game->chight = game->yplayer;
    //         game->cwidth = game->xplayer;
    //         lift_rays(game, map, b);
    //         b++;
    //     }
    //     b = 1;
    //     while(b < game->size)
    //     {
    //         game->chight = game->yplayer;
    //         game->cwidth = game->xplayer;
    //         right_rays(game, map, b);
    //         b++;            
    //     }
    // }
    // if (map->player == 'S')
    // {}
    // if (map->player == 'W')
    // {}
}
