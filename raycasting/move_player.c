/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:17:12 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/21 13:56:40 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void    ft_up(t_game *game)
{
    if ((game->yplayer - 3) >= 0 && game->t_map->maps[(game->yplayer - 2) / game->size][game->xplayer / game->size] != '1')
    {
        game->x = (game->xplayer / game->size);
        game->y = (game->yplayer / game->size);
        put_ground(game, game->t_map);
        game->yplayer -=1;
        game->y = (game->yplayer / game->size);
        put_player(game);
        draw_grid(game, game->t_map);
        game->rotatangle += 1 * (2 * (M_PI / 180));
        shut_rays(game, game->t_map);

    }
}

void    ft_down(t_game *game)
{
    if ((game->yplayer + 2) < ft_wc_l(game->t_map->maps) * game->size && game->t_map->maps[(game->yplayer + 2) / game->size][game->xplayer / game->size] != '1')
    {
        game->x = (game->xplayer / game->size);
        game->y = (game->yplayer / game->size);
        put_ground(game, game->t_map);
        game->yplayer +=1;
        game->y = (game->yplayer / game->size);
        put_player(game);
        draw_grid(game, game->t_map);
        shut_rays(game, game->t_map);

    }
}

void    ft_right(t_game *game)
{
    if ((game->xplayer + 2) < ft_len(game->t_map->maps[game->yplayer / game->size]) * game->size && game->t_map->maps[game->yplayer / game->size][(game->xplayer + 2) / game->size] != '1')
    {
        game->x = (game->xplayer / game->size);
        game->y = (game->yplayer / game->size);
        put_ground(game, game->t_map);
        game->xplayer +=1;
        game->x = (game->xplayer / game->size);
        put_player(game);
        draw_grid(game, game->t_map);
        shut_rays(game, game->t_map);

    }
}

void    ft_lift(t_game *game)
{
    if ((game->xplayer - 3) > 0 && game->t_map->maps[game->yplayer / game->size][(game->xplayer - 2) / game->size] != '1')
    {
        game->x = (game->xplayer / game->size);
        game->y = (game->yplayer / game->size);
        put_ground(game, game->t_map);
        game->xplayer -=1;
        game->y = (game->yplayer / game->size);
        put_player(game);
        draw_grid(game, game->t_map);
        shut_rays(game, game->t_map);
    }
}
