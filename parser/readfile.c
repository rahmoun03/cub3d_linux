#include "../cub.h"

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

void wc_space(t_map *map, char **str)
{
	int i;
	int j;

	i = 0;
	map->spaces = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if(str[i][j] == ' ')
				map->spaces++;
			j++;
		}
		i++;
	}
}

void    read_file(t_map *map, int fd)
{
	int i = 0;
    map->dst = get_next_line(fd);
    while (map->dst != NULL)
    {
        map->map = ft_strjoin(map->map, map->dst);
		if (i > 0)
        	free(map->dst);
		i++;
        map->dst = get_next_line(fd);
    }
	check_element(map);
	check_c_f(map);
	check_map(map);
	map_closed(map);
	double_nl(map);
}

void	ft_free_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		free(tmp[i++]);
}

int	item_chr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && c != s[i])
		i++;
	if (c == s[i])
		return (i);
	return (-1);
}

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

void 	map_closed(t_map *map)
{
	t_ft	*tmp;
	int i = 0;

	tmp = (t_ft *)malloc(sizeof(t_ft));
	tmp->i = 0;
	tmp->j = -1;
	tmp->maps = ft_split((map->map) + map->i, '\n');
	tmp->colum = ft_wc_l(tmp->maps);
	wc_space(map, tmp->maps);
	tmp->spaces = map->spaces;
	while (tmp->maps[tmp->i] && tmp->j == -1)
		tmp->j = item_chr(tmp->maps[tmp->i++], map->player);
	tmp->i--;
	flood_fill(tmp, tmp->i, tmp->j);
	wc_space(map, tmp->maps);
	if(tmp->spaces != map->spaces)
	{
		printf("Error map_closed()\n");
		exit(0);
	}
	while(tmp->maps[i])
	{
		printf("%s\n", tmp->maps[i]);
		i++;
	}
		
	ft_free_tmp(tmp->maps);
	free(tmp->maps);
	free(tmp);
}

void	flood_fill(t_ft *tmp, int i, int j)
{
	if (i <= 0 || j <= 0 || i > tmp->colum
		|| tmp->maps[i] != NULL || tmp->maps[i][j] == '*')
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

int ft_iss_digit(char c) 
{
    return c >= '0' && c <= '9';
}

void c_f_first(char **numbers) 
{
    int i; 
	int j;
    int last_digit;

    i = 0;
    while (numbers[i]) 
	{
        j = 0;
        last_digit = 0; 

        while (numbers[i][j]) 
		{
            if (ft_iss_digit(numbers[i][j])) 
			{
                last_digit = 1; 
                j++;
            } 
			else if (numbers[i][j] == ' ') 
			{
                if (last_digit && numbers[i][j + 1] != '\0' && ft_iss_digit(numbers[i][j + 1])) 
				{
                    printf("Error Space inside a number in '%s'\n", numbers[i]);
                    exit(0);
                }
                j++;
            } 
			else 
			{
                printf("Error : c_f_first(non-digit character '%c')\n", numbers[i][j]);
                exit(0);
            }
        }
        i++;
    }

    if (i != 3 || numbers[3] != NULL) 
	{
        printf("Error : Incorrect number of elements in c_f_first()\n");
        exit(0);
    }
}

void	c_f_end(t_map *map)
{
	if(map->ceiling.r > 255 || map->ceiling.g > 255 || map->ceiling.b > 255)
	{
		printf("Error : number c_f_end()\n");
		exit(0);
	}
	if(map->ceiling.r < 0 || map->ceiling.g < 0 || map->ceiling.b < 0)
	{
		printf("Error : number c_f_end()\n");
		exit(0);
	}
	if(map->floor.r > 255 || map->floor.g > 255 || map->floor.b > 255)
	{
		printf("Error : number c_f_end()\n");
		exit(0);
	}
	if(map->floor.r < 0 || map->floor.g < 0 || map->floor.b < 0)
	{
		printf("Error : number c_f_end()\n");
		exit(0);
	}
}

void	check_c_f(t_map *map)
{
	map->ceiling.numbers = ft_split(map->c, ',');
	map->floor.numbers = ft_split(map->f, ',');

	// ceiling
	c_f_first(map->ceiling.numbers);
	map->ceiling.r = ft_atoi(map->ceiling.numbers[0]);
	map->ceiling.g = ft_atoi(map->ceiling.numbers[1]);
	map->ceiling.b = ft_atoi(map->ceiling.numbers[2]);
	// floor
	c_f_first(map->floor.numbers);
 	map->floor.r = ft_atoi(map->floor.numbers[0]);
	map->floor.g = ft_atoi(map->floor.numbers[1]);
	map->floor.b = ft_atoi(map->floor.numbers[2]);

	c_f_end(map);
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
			{
				map->player = map->map[i];
				player++;
			}
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
	char *path;

	if (str[map->i] == 'N' && str[map->i + 1] && str[map->i + 1] == 'O')	
	{
        map->i += 2;
        path = set_path(map, str);
        if (!check_path(path, ".xpm")) 
		{
            printf("Erreur Le chemin de la texture 'NO' ne se termine pas par '.xpm'\n");
            free(path);
            return 0;
        }
        map->no = path;
        return 1;
    }
	if (str[map->i] == 'S' && str[map->i + 1] && str[map->i + 1] == 'O')	
	{
        map->i += 2;
        path = set_path(map, str);
        if (!check_path(path, ".xpm")) 
		{
            printf("Erreur Le chemin de la texture 'SO' ne se termine pas par '.xpm'\n");
            free(path);
            return 0;
        }
        map->so = path;
        return 1;
    }
	if (str[map->i] == 'W' && str[map->i + 1] && str[map->i + 1] == 'E')	
	{
        map->i += 2;
        path = set_path(map, str);
        if (!check_path(path, ".xpm")) 
		{
            printf("Erreur Le chemin de la texture 'WE' ne se termine pas par '.xpm'\n");
            free(path);
            return 0;
        }
        map->we = path;
        return 1;
    }
	if (str[map->i] == 'E' && str[map->i + 1] && str[map->i + 1] == 'A')	
	{
        map->i += 2;
        path = set_path(map, str);
        if (!check_path(path, ".xpm")) 
		{
            printf("Erreur Le chemin de la texture 'EA' ne se termine pas par '.xpm'\n");
            free(path);
            return 0;
        }
        map->ea = path;
        return 1;
    }
	return 0;
}

int check_commas(const char *str, int start, int end) 
{
    int count = 0;
	int i = start;
	while(i < end)
	{
		 if (str[i] == ',')
            count++;
		i++;
	}
    return count == 2;
}

void check_and_set(t_map *map, char *str) 
{
    if (!check_texture(map, str))
	{
        int start = map->i;
        int end = start;

        while (str[end] != '\0' && str[end] != '\n') 
            end++;

        if (str[map->i] == 'C' && (str[map->i + 1] == ' ' || str[map->i + 1] == '\t')) 
		{
            if (!check_commas(str, start, end)) 
			{
                printf("Erreur: Nombre incorrect de virgules pour 'C'\n");
                exit(0);
            }
            map->i++;
            map->c = set_path(map, str);
        }
        else if (str[map->i] == 'F' && (str[map->i + 1] == ' ' || str[map->i + 1] == '\t')) 
		{
            if (!check_commas(str, start, end)) 
			{
                printf("Erreur: Nombre incorrect de virgules pour 'F'\n");
                exit(0);
            }
            map->i++;
            map->f = set_path(map, str);
        }
        else 
		{
            printf("Erreur : check_and_set()\n");
            exit(0);
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
