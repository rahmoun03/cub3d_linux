/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile_continue3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:06:27 by bel-kase          #+#    #+#             */
/*   Updated: 2023/12/08 21:22:33 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_wc_l(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_iss_digit(char c)
{
	return (c >= '0' && c <= '9');
}

void	flood_fill(t_ft *tmp, int i, int j)
{
	if (i <= 0 || j <= 0 || i > tmp->colum || tmp->maps[i][j] == '*')
		return ;
	tmp->maps[i][j] = '*';
	if (tmp->maps[i][j + 1] && tmp->maps[i][j + 1] != '1')
		flood_fill(tmp, i, j + 1);
	if (tmp->maps[i + 1][j] && tmp->maps[i + 1][j] != '1')
		flood_fill(tmp, i + 1, j);
	if (i - 1 >= 0 && tmp->maps[i - 1][j] && tmp->maps[i - 1][j] != '1')
		flood_fill(tmp, i - 1, j);
	if (j - 1 >= 0 && tmp->maps[i][j - 1] && tmp->maps[i][j - 1] != '1')
		flood_fill(tmp, i, j - 1);
}

void	check_c_f(t_map *map)
{
	map->ceiling.numbers = ft_split(map->c, ',');
	map->floor.numbers = ft_split(map->f, ',');
	c_f_first(map->ceiling.numbers);
	map->ceiling.r = ft_atoi(map->ceiling.numbers[0]);
	map->ceiling.g = ft_atoi(map->ceiling.numbers[1]);
	map->ceiling.b = ft_atoi(map->ceiling.numbers[2]);
	c_f_first(map->floor.numbers);
	map->floor.r = ft_atoi(map->floor.numbers[0]);
	map->floor.g = ft_atoi(map->floor.numbers[1]);
	map->floor.b = ft_atoi(map->floor.numbers[2]);
	c_f_end(map);
}
