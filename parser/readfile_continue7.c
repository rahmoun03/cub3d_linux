#include "../cub.h"


void	set_path_with_check(t_map *map, char *str, int start, int end,
		char type)
{
	if (!check_commas(str, start, end))
	{
		printf("Erreur: Nombre incorrect de virgules pour '%c'\n", type);
		exit(0);
	}
	map->i++;
	if (type == 'C')
		map->c = set_path(map, str);
	else if (type == 'F')
		map->f = set_path(map, str);
}

void check_and_set(t_map *map, char *str) 
{
    int start, end;

    if (!check_texture(map, str)) 
    {
        start = map->i;
        end = start;
        while (str[end] != '\0' && str[end] != '\n')
            end++;

        if (str[map->i] == 'C' && (str[map->i + 1] == ' ' || str[map->i + 1] == '\t')) 
            set_path_with_check(map, str, start, end, 'C');
        else if (str[map->i] == 'F' && (str[map->i + 1] == ' ' || str[map->i + 1] == '\t')) 
            set_path_with_check(map, str, start, end, 'F');
        else 
        {
            printf("Erreur : check_and_set()\n");
            exit(0);
        }
    }
}

int	check_commas(const char *str, int start, int end)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (i < end)
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count == 2);
}
