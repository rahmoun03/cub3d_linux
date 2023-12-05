/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:17:12 by arahmoun          #+#    #+#             */
/*   Updated: 2023/12/05 05:41:41 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int check_player_move(t_game *game, int x, int y)
{
    if (game->t_map->maps[(y / SIZE)][(x / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[(y / SIZE)][((x + 1) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[(y / SIZE)][((x - 1) / SIZE)] == '1')
        return 0;

    if (game->t_map->maps[((y + 1) / SIZE)][((x + 1) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[((y + 1) / SIZE)][((x - 1) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[((y + 1) / SIZE)][(x / SIZE)] == '1')
        return 0;
    
    if (game->t_map->maps[((y - 1) / SIZE)][((x + 1) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[((y - 1) / SIZE)][((x - 1) / SIZE)] == '1')
        return 0;
    if (game->t_map->maps[((y - 1) / SIZE)][(x / SIZE)] == '1')
        return 0;
    
    return 1;
}

void    ft_up(t_game *game)
{
    float x = game->xplayer + cos(game->rotatangle) * 4;
    float y = game->yplayer + sin(game->rotatangle) * 4;
    if (check_player_move(game, x, y))
    {
        game->xplayer = x;
        game->yplayer = y;
    }
}

void    ft_down(t_game *game)
{
    float x = game->xplayer - cos(game->rotatangle) * 4;
    float y = game->yplayer - sin(game->rotatangle) * 4;
    if ((y) < ft_wc_l(game->t_map->maps) * SIZE && check_player_move(game, x, y))
    {
        game->xplayer = x;
        game->yplayer = y;
    }
}

void    ft_right(t_game *game)
{
    double east = fmod((game->rotatangle + PI / 2), (2 * PI));
    float x = game->xplayer + cos(east) * 4;
    float y = game->yplayer + sin(east) * 4;
    if (x < ft_len(game->t_map->maps[(int)(y / SIZE)]) * SIZE && check_player_move(game, x, y))
    {
        game->xplayer = x;
        game->yplayer = y;
    }
}

void    ft_lift(t_game *game)
{
    double west = fmod((game->rotatangle - PI / 2 + 2 * PI), (2 * PI));
    float x = game->xplayer + cos(west) * 4;
    float y = game->yplayer + sin(west) * 4;
    if (check_player_move(game, x, y))
    {
        game->xplayer = x;
        game->yplayer = y;
    }
}

void    ft_rotat_right(t_game *game)
{
    game->rotatangle += 4 * (PI / 180);
}

void    ft_rotat_lift(t_game *game)
{
    game->rotatangle -= 4 * (PI / 180);
}
