/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:31:39 by arahmoun          #+#    #+#             */
/*   Updated: 2023/08/01 20:06:37 by arahmoun         ###   ########.fr       */
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
	map->maps = ft_split(map->map, '\n');
	for (int k = 0; map->maps[k]; k++)
	{
		printf("%s\n", map->maps[k]);
	}
}

char	*set_path(t_map *map, char *str, int i)
{
	char *dst;

	dst = NULL;
	if (str[i] == ' ' || str[i] == '\t')
	{
		while ((str[i] == ' ') || (str[i] == '\t'))
			i++;
		dst = (char *)malloc(ft_strlen(str + i) + 1);
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
	if (str[i] == 'N' && str[i + 1] == 'O')
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
	int j;

	i = 0;
	while (map->maps[i] && i < 6)
	{
		j = 0;
		while (map->maps[i][j] && map->maps[i][j] == ' ')
				j++;
		if (map->maps[i][j] == 'N' || map->maps[i][j] == 'S'
			|| map->maps[i][j] == 'W' || map->maps[i][j] == 'E'
			|| map->maps[i][j] == 'F' || map->maps[i][j] == 'C')
		{
			check_and_set(map, map->maps[i], j);
		}
		else
		{
			printf("Error\n");
			exit(1);
		}
		i++;
	}
}