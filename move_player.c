#include "cub.h"

void	move_up(t_game *game, t_map *ptr)
{
	if (ptr->maps[(game->ylpayer / 10) - 1][game->xlpayer
		/ 10] != '1' && ptr->maps[(game->ylpayer / 10) - 1][game->xlpayer
		/ 10] != 'E')
	{
		put_image(game, ptr->so);
		game->ylpayer -= 10;
		put_image(game, ptr->so);
		put_player(game);
	}
	else if (game->start > 2 && ptr->maps[(game->ylpayer / 10)
			- 1][game->xlpayer / 10] != '1')
	{
		put_image(game, ptr->so);
		game->ylpayer -= 10;
		put_player(game);
		exit(0);
	}
}

void	ft_up(t_game *game, t_map *ptr)
{
    move_up(game, ptr);
}
