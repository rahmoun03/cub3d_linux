/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahmoun <arahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:31:39 by arahmoun          #+#    #+#             */
/*   Updated: 2023/11/16 00:07:01 by arahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void double_nl(t_map *map)
{
	int i;

	i = map->i;
	while (map->map[i])
	{
		if ( map->map[i] == '\n' && map->map[map->i + 1]
			&& map->map[i + 1] == '\n')
		{
			printf("Error : double_nl()\n");
			exit(1);
		}
		i++;
	}
}

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
	check_map(map);
	double_nl(map);
	for (int k = map->i; map->map[k]; k++)
	{
		printf("%c", map->map[k]);
	}
}

void	check_map(t_map *map)
{
	int i;
	int	player;

	i = map->i;
	player = 0;
	while (map->map[i] != '\0')
	{
		if(map->map[i] == '1' || map->map[i] == '0'
			|| map->map[i] == 'W' || map->map[i] == 'S'
			|| map->map[i] == 'E' || map->map[i] == 'N'
			|| map->map[i] == ' ' || map->map[i] == '\n')
		{

			if(map->map[i] == 'W' || map->map[i] == 'S'
				|| map->map[i] == 'E' || map->map[i] == 'N')
				player++;
			i++;
		}
		else
		{
			printf("Error : check_map(%d) %c\n", i, map->map[i]);
			exit(1);
		}
	}
	if (player != 1)
	{
		printf("Error : check_map(player) \n");
		exit(1);
	}
}

char	*set_path(t_map *map, char *str)
{
	char *dst;
	int j;

	dst = NULL;
	if (str[map->i] == ' ' || str[map->i] == '\t')
	{
		while (str[map->i] && (str[map->i] == ' ' || str[map->i] == '\t'))
			map->i++;
		j = 0;
		while (str[map->i + j] && str[map->i + j] != '\n')
			j++;
		dst = (char *)malloc(j + 1);
		map->j = 0;
		while (str[map->i] && str[map->i] != '\n')
			dst[map->j++] = str[map->i++];
		dst[map->j] = '\0';
		return (dst); 
	}
	else
	{
		printf("Error : set_path()\n");
		exit (0);
	}
}

int check_texture(t_map *map, char *str)
{
	if (str[map->i] == 'N' && str[map->i + 1] && str[map->i + 1] == 'O')
	{ 
		map->i += 2;
		map->no = set_path(map, str);
		return 1;
	}
	else if (str[map->i] == 'S' && str[map->i + 1] == 'O')
	{
		map->i += 2;
		map->so = set_path(map, str);
		return 1;
	}
	else if (str[map->i] == 'W' && str[map->i + 1] == 'E')
	{
		map->i += 2;
		map->we = set_path(map, str);
		return 1;
	}
	else if (str[map->i] == 'E' && str[map->i + 1] == 'A')
	{
		map->i += 2;
		map->ea = set_path(map, str);
		return 1;
	}
	return 0;
}

void	check_and_set(t_map *map, char *str)
{
	if (!check_texture(map, str))
	{
		if (str[map->i] == 'C'
			&& (str[map->i + 1] == ' ' || str[map->i + 1] == '\t'))
		{
			map->i++;
			map->c = set_path(map, str);
		}
		else if (str[map->i] == 'F'
			&& (str[map->i + 1] == ' ' || str[map->i + 1] == '\t'))
		{
			map->i++;
			map->f = set_path(map, str);
		}
		else
		{
			printf("Error : check_and_set()\n");
			exit (0);
		}
	}
}

int element_is_full(t_map *map)
{
	if (map->c && map->f && map->ea
		&& map->no && map->so && map->we)
		return 1;
	return 0;
}

void	check_element(t_map *map)
{
	map->i = 0;
	while (map->map[map->i] && !element_is_full(map))
	{
		while (map->map[map->i] && (map->map[map->i] == ' ' || map->map[map->i] == '\t' || map->map[map->i] == '\n'))
				map->i++;
		if (map->map[map->i] == 'N' || map->map[map->i] == 'S'
			|| map->map[map->i] == 'W' || map->map[map->i] == 'E'
			|| map->map[map->i] == 'F' || map->map[map->i] == 'C')
		{
			check_and_set(map, map->map);
		}
		else
		{
			printf("Error : check_element(%d) = %c\n", map->i , map->map[map->i]);
			exit(1);
		}
		map->i++;
	}
	while (map->map[map->i] && map->map[map->i] == '\n')
		map->i++;
}