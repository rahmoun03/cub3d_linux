/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:17:12 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/22 09:49:11 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void    ft_up(t_game *game)
{
    if ((game->yplayer - 3) >= 0 && game->t_map->maps[(game->yplayer - 2) / game->size][game->xplayer / game->size] != '1')
    {
        put_ground(game, game->t_map);
        game->yplayer += sin(game->rotatangle);
        put_player(game);
        draw_grid(game, game->t_map);
        shut_rays(game, game->t_map);

    }
}

void    ft_down(t_game *game)
{
    if ((game->yplayer + 2) < ft_wc_l(game->t_map->maps) * game->size && game->t_map->maps[(game->yplayer + 2) / game->size][game->xplayer / game->size] != '1')
    {
        put_ground(game, game->t_map);
        game->yplayer += cos(game->rotatangle);
        put_player(game);
        draw_grid(game, game->t_map);
        shut_rays(game, game->t_map);

    }
}

void    ft_right(t_game *game)
{
    if ((game->xplayer + 2) < ft_len(game->t_map->maps[game->yplayer / game->size]) * game->size && game->t_map->maps[game->yplayer / game->size][(game->xplayer + 2) / game->size] != '1')
    {
        put_ground(game, game->t_map);
        game->xplayer += cos(game->rotatangle);
        put_player(game);
        draw_grid(game, game->t_map);
        shut_rays(game, game->t_map);

    }
}

void    ft_lift(t_game *game)
{
    if ((game->xplayer - 3) > 0 && game->t_map->maps[game->yplayer / game->size][(game->xplayer - 2) / game->size] != '1')
    {
        put_ground(game, game->t_map);
        game->xplayer += sin(game->rotatangle);
        put_player(game);
        draw_grid(game, game->t_map);
        shut_rays(game, game->t_map);
    }
}

void    ft_rotat_right(t_game *game)
{

    put_ground(game, game->t_map);
    put_player(game);
    draw_grid(game, game->t_map);
    game->rotatangle += 1 * (4 * (M_PI / 360));
    shut_rays(game, game->t_map);

}

void    ft_rotat_lift(t_game *game)
{

    put_ground(game, game->t_map);
    put_player(game);
    draw_grid(game, game->t_map);
    game->rotatangle -= 1 * (4 * (M_PI / 360));
    shut_rays(game, game->t_map);
}
