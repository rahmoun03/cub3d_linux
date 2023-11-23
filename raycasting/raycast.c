/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:23:47 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/23 17:28:52 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


void    shut_rays(t_game *game, t_map *map)
{

    int pix ;
    int i = 0;

    while (i < 10)
    {
        pix = 0;
        while(map->maps[(int)(game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix) / game->size][(int)(game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix) / game->size] != '1')
        {
            my_mlx_pixel_put(game, game->xplayer + cos(game->rotatangle + i * game->rotatspeed) * pix,
            game->yplayer + sin(game->rotatangle + i * game->rotatspeed) * pix, 16711680);
            pix++;
        }
        i++;
    }
    // mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

}
