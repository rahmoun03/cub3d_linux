/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:44:03 by bel-kase          #+#    #+#             */
/*   Updated: 2023/12/09 10:52:48 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	error_texture(char *str, int fd)
{
	close(fd);
	printf("Error : texture path is invalid (%s)\n", str);
	exit(0);
}

void	flood_fill(t_ft *tmp, int i, int j)
{
	if (i < 0 || j < 0 || i >= tmp->colum
		|| j >= ft_len(tmp->maps[i]) || tmp->maps[i][j] == '*')
		return ;
	tmp->maps[i][j] = '*';
	if (tmp->maps[i] && (j < ft_len(tmp->maps[i]))
		&& tmp->maps[i][j + 1]
		&& tmp->maps[i][j + 1] != '1')
		flood_fill(tmp, i, j + 1);
	if ((tmp->maps[i + 1])
		&& (j < ft_len(tmp->maps[i + 1]))
		&& (tmp->maps[i + 1][j] && tmp->maps[i + 1][j] != '1'))
		flood_fill(tmp, i + 1, j);
	if ((i - 1 >= 0 && tmp->maps[i - 1])
		&& (j < ft_len(tmp->maps[i - 1]))
		&& (tmp->maps[i - 1][j] && tmp->maps[i - 1][j] != '1'))
		flood_fill(tmp, i - 1, j);
	if (j - 1 >= 0 && tmp->maps[i]
		&& tmp->maps[i][j - 1] != '1')
		flood_fill(tmp, i, j - 1);
}
