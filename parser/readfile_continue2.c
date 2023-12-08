#include "../cub.h"

void	ft_free_tmp_g(char **tmp)
{
	int	i;

	if (tmp == NULL)
		return ;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	check_wall_line(char *line, int width, char *error_message)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (line[i] == '0')
		{
			printf("%s\n", error_message);
			exit(1);
		}
		i++;
	}
}

void	check_side_walls(char **lines, int height, char *error_message)
{
	int	i;
	int	width;

	i = 0;
	while (i < height)
	{
		width = ft_len(lines[i]);
		if (lines[i][0] == '0' || lines[i][width - 1] == '0')
		{
			printf("%s\n", error_message);
			exit(1);
		}
		i++;
	}
}

void	check_walls(t_map *map)
{
	char	**lines;
	int		height;

	lines = ft_split((map->map) + map->i, '\n');
	height = ft_wc_l(lines);
	check_wall_line(lines[0], ft_len(lines[0]),
		"Error: Maps n'est pas entoure de (1)");
	check_wall_line(lines[height - 1], ft_len(lines[height - 1]),
		"Error: Maps n'est pas entoure de (1)");
	check_side_walls(lines, height,
		"Error: Maps n'est pas entoure de (1)");
	ft_free_tmp_g(lines);
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