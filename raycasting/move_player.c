/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:17:12 by arahmoun          #+#    #+#             */
/*   Updated: 2023/12/06 00:23:25 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int check_player_move(t_game *game, int x, int y)
{
    if (game->t_map->maps[(y / SIZE)][(x / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[(y / SIZE)][((x + 10) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[(y / SIZE)][((x - 10) / SIZE)] == '1')
        return 0;

    if (game->t_map->maps[((y + 10) / SIZE)][((x + 10) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[((y + 10) / SIZE)][((x - 10) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[((y + 10) / SIZE)][(x / SIZE)] == '1')
        return 0;
    
    if (game->t_map->maps[((y - 10) / SIZE)][((x + 10) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[((y - 10) / SIZE)][((x - 10) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[((y - 10) / SIZE)][(x / SIZE)] == '1')
        return 0;
    
    return 1;
}

void    ft_up(t_game *game)
{
    float x = game->xplayer + cos(game->rotatangle) * 5;
    float y = game->yplayer + sin(game->rotatangle) * 5;
    if (check_player_move(game, x, y))
    {
        game->xplayer = x;
        game->yplayer = y;
    }
}

void    ft_down(t_game *game)
{
    float x = game->xplayer - cos(game->rotatangle) * 5;
    float y = game->yplayer - sin(game->rotatangle) * 5;
    if ((y) < ft_wc_l(game->t_map->maps) * SIZE && check_player_move(game, x, y))
    {
        game->xplayer = x;
        game->yplayer = y;
    }
}

void    ft_right(t_game *game)
{
    double east = fmod((game->rotatangle + PI / 2), (2 * PI));
    float x = game->xplayer + cos(east) * 5;
    float y = game->yplayer + sin(east) * 5;
    if (x < ft_len(game->t_map->maps[(int)(y / SIZE)]) * SIZE && check_player_move(game, x, y))
    {
        game->xplayer = x;
        game->yplayer = y;
    }
}

void    ft_lift(t_game *game)
{
    double west = fmod((game->rotatangle - PI / 2 + 2 * PI), (2 * PI));
    float x = game->xplayer + cos(west) * 5;
    float y = game->yplayer + sin(west) * 5;
    if (check_player_move(game, x, y))
    {
        game->xplayer = x;
        game->yplayer = y;
    }
}

void    ft_rotat_right(t_game *game)
{
    game->rotatangle += 5 * (PI / 180);
}

void    ft_rotat_lift(t_game *game)
{
    game->rotatangle -= 5 * (PI / 180);
}
