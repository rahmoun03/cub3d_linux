/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:17:12 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/25 10:47:29 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void    ft_up(t_game *game)
{
    if (game->t_map->maps[(int)(game->yplayer + sin(game->rotatangle)) / SIZE][game->xplayer / SIZE] != '1')
    {
        game->yplayer += sin(game->rotatangle);
    }
}

void    ft_down(t_game *game)
{
    if ((game->yplayer + 1) < ft_wc_l(game->t_map->maps) * SIZE && game->t_map->maps[(int)(game->yplayer + cos(game->rotatangle)) / SIZE][game->xplayer / SIZE] != '1')
    {
        game->yplayer += cos(game->rotatangle);
    }
}

void    ft_right(t_game *game)
{
    int x = (int)(game->xplayer  + cos(game->rotatangle * game->rotatspeed)) / SIZE;
    int y = game->yplayer / SIZE;
    if ((game->xplayer + 1) < ft_len(game->t_map->maps[y]) * SIZE && game->t_map->maps[y][x] != '1')
    {
        game->xplayer +=  cos(game->rotatangle * game->rotatspeed) * 1;
    }
}

void    ft_lift(t_game *game)
{
    int x = (int)(game->xplayer + cos(game->rotatangle * game->rotatspeed)) / SIZE;
    int y = game->yplayer / SIZE;
    if (game->t_map->maps[y][x] != '1')
    {
        game->xplayer +=  cos(game->rotatangle * game->rotatspeed) * 1;
    }
}

void    ft_rotat_right(t_game *game)
{
    game->rotatangle += 0.13;
}

void    ft_rotat_lift(t_game *game)
{

    game->rotatangle -= 0.13;
}
