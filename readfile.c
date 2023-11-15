/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:31:39 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/15 18:10:50 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    read_file(t_map *map, int fd)
{
	int i = 0;
    map->map = NULL;
    map->dst = get_next_line(fd);
    while (map->dst)
    {
        map->map = ft_strjoin(map->map, map->dst);
		if (i > 0)
        	free(map->dst);
		i++;
        map->dst = get_next_line(fd);
    }
	check_element(map);
	map->maps = ft_split(map->map, '\n');
	for (int k = 0; map->maps[k]; k++)
	{
		printf("%s\n", map->maps[k]);
	}
}

char	*set_path(t_map *map, char *str, int i)
{
	char *dst;
	int j;

	j = 0;
	dst = NULL;
	if (str[i] == ' ' || str[i] == '\t')
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		while (str[i + j] && str[i + j] != '\n')
			j++;
		dst = (char *)malloc(j + 1);
		map->i = 0;
		while (str[i])
			dst[map->i++] = str[i++];
		dst[map->i] = '\0';
		return (dst); 
	}
	else
		exit (0);
}

void	check_and_set(t_map *map, char *str, int i)
{
	if (str[i] == 'N' && str[i + 1] && str[i + 1] == 'O')
		map->no = set_path(map, str, i+2);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		map->so = set_path(map, str, i+2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		map->we = set_path(map, str, i+2);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		map->ea = set_path(map, str, i+2); 
	else if (str[i] == 'C')
		map->c = set_path(map, str, i+1);
	else if (str[i] == 'F')
		map->f = set_path(map, str, i+1);
	else
		exit (0);
}

void	check_element(t_map *map)
{
	int i;

	i = 0;
	while (map->map[i])
	{
		while (map->map[i] && (map->map[i] == ' ' || map->map[i] == '\t'))
				i++;
		if (map->map[i] == 'N' || map->map[i] == 'S'
			|| map->map[i] == 'W' || map->map[i] == 'E'
			|| map->map[i] == 'F' || map->map[i] == 'C')
		{
			check_and_set(map, map->map, i);
		}
		else if (map->c || map->f || map->ea
				|| map->no || map->so || map->we)
		{
		}
		else
		{
			printf("Error\n");
			exit(1);
		}
		i++;
	}
}