#include "../cub.h"

void init_textures(t_game *game) 
{
    game->north.img = mlx_xpm_file_to_image(game->mlx, game->t_map->no, &game->north.weight, &game->north.height);
    game->north.addr = mlx_get_data_addr(game->north.img, &game->north.bits_per_pixel, &game->north.line_length, &game->north.endian);
    game->south.img = mlx_xpm_file_to_image(game->mlx, game->t_map->so, &game->south.weight, &game->south.height);
    game->south.addr = mlx_get_data_addr(game->south.img, &game->south.bits_per_pixel, &game->south.line_length, &game->south.endian);
    game->west.img = mlx_xpm_file_to_image(game->mlx, game->t_map->we, &game->west.weight, &game->west.height);
    game->west.addr = mlx_get_data_addr(game->west.img, &game->west.bits_per_pixel, &game->west.line_length, &game->west.endian);
    game->east.img = mlx_xpm_file_to_image(game->mlx, game->t_map->ea, &game->east.weight, &game->east.height);
    game->east.addr = mlx_get_data_addr(game->east.img, &game->east.bits_per_pixel, &game->east.line_length, &game->east.endian);
}


int check_color(t_game *game, int x_pos, int y_pos ,int xp, int yp)
{
    if (game->t_map->maps[y_pos / SIZE][((x_pos + 1)/ SIZE)] == '1')// limn 
        return get_pixel_img(game->east, xp, yp); 
    else if (game->t_map->maps[((y_pos + 1)/ SIZE)][x_pos / SIZE] == '1') // lta7t 
        return get_pixel_img(game->south, xp, yp);
    else if (game->t_map->maps[(y_pos) / SIZE][((x_pos - 1) / SIZE)] == '1') // lisr 
         return get_pixel_img(game->west, xp, yp);
    else if (game->t_map->maps[((y_pos - 1) / SIZE)][x_pos / SIZE] == '1') // lfo9
        return get_pixel_img(game->north, xp, yp);
    return 0;
}

int check_rays_2D(t_game *game, t_map *map, int pix, double x, double y)
{
	if(map->maps[(int)((y + (sin(game->rotatangle + game->rayangle) * pix)) - 1) / 10]
        [(int)(x + (cos(game->rotatangle + game->rayangle) * pix)) / 10] == '1')
		return 0;
	else if(map->maps[(int)((y + (sin(game->rotatangle + game->rayangle) * pix)) + 1) / 10]
		[(int)(x + (cos(game->rotatangle + game->rayangle) * pix)) / 10] == '1')
		return 0;
	else if(map->maps[(int)((y + (sin(game->rotatangle + game->rayangle) * pix))) / 10]
		[(int)((x + (cos(game->rotatangle + game->rayangle) * pix)) + 1) / 10] == '1')
		return 0;
	else if(map->maps[(int)((y + (sin(game->rotatangle + game->rayangle) * pix))) / 10]
		[(int)((x + (cos(game->rotatangle + game->rayangle) * pix)) - 1) / 10] == '1')
		return 0;
	return (1);
}

int check_rays_3D(t_game *game, t_map *map, int pix)
{
	if(map->maps[(int)((game->yplayer + (sin(game->rotatangle + game->rayangle) * pix)) - 1) / SIZE]
        [(int)(game->xplayer + (cos(game->rotatangle + game->rayangle) * pix)) / SIZE] == '1')
		return 0;
	else if(map->maps[(int)((game->yplayer + (sin(game->rotatangle + game->rayangle) * pix)) + 1) / SIZE]
		[(int)(game->xplayer + (cos(game->rotatangle + game->rayangle) * pix)) / SIZE] == '1')
		return 0;
	else if(map->maps[(int)((game->yplayer + (sin(game->rotatangle + game->rayangle) * pix))) / SIZE]
		[(int)((game->xplayer + (cos(game->rotatangle + game->rayangle) * pix)) + 1) / SIZE] == '1')
		return 0;
	else if(map->maps[(int)((game->yplayer + (sin(game->rotatangle + game->rayangle) * pix))) / SIZE]
		[(int)((game->xplayer + (cos(game->rotatangle + game->rayangle) * pix)) - 1) / SIZE] == '1')
		return 0;
	return (1);
}

void    print_wall(t_game *game, int x_pos, int y_pos, int pix)
{
    float dark = 1;
    int ceiling = (game->t_map->ceiling.r << 16) + (game->t_map->ceiling.g << 8) + game->t_map->ceiling.b;
    int floor = (game->t_map->floor.r << 16) + (game->t_map->floor.g << 8) + game->t_map->floor.b;
    int top = (HEIGHT / 2) - game->projectedWallHeight / 2;
    int bottom = top + game->projectedWallHeight;
    game->y = 0;
    int	ofx = 0;
    int	ofy = 0;
    while (game->y < top)
    {
        my_mlx_pixel_put(game, game->x, game->y, ceiling);
        if(game->y + 150 >= HEIGHT / 2)
        {
            shadow(game, game->x, game->y, ceiling, dark);
            if(dark > 0.05 && game->y % 4 == 0)
                dark -= 0.05;
        }
        game->y++;
    }
    dark = 0.0;
	if (game->virti == 0)
	{
		ofx = fmod(x_pos, SIZE);
		if (ofx >= SIZE - 1 || ofx == 0)
			ofx = fmod(y_pos, SIZE);
	}
	else if (game->virti == 1)
    {
		ofx = fmod(x_pos, SIZE);
        if (ofx >= SIZE - 1  || ofx == 0)
			ofx = fmod(y_pos, SIZE);

    }
    dark = 0.0;
    while (game->y <= bottom)
    {
        ofy = fmod(((game->y - (HEIGHT - game->projectedWallHeight) / 2) * SIZE) / game->projectedWallHeight,SIZE);
        int color = check_color(game, x_pos, y_pos, ofx, ofy);
        if ( color != -16777216)
            my_mlx_pixel_put(game, game->x, game->y, color);
        if(pix > 900)
            shadow(game, game->x, game->y, color, (10 - ((float)pix / 100)));
        if(game->y > (HEIGHT / 2) + 40 && game->y < (HEIGHT / 2) + 300)
        {
            if(dark < 1 && game->y % 4 == 0)
                dark += 0.03;
        }
        game->y++;
    }
    while (game->y < HEIGHT)
    {
        my_mlx_pixel_put(game, game->x, game->y, floor);
        if(game->y > (HEIGHT / 2) + 30 && game->y < (HEIGHT / 2) + 300)
        {
            shadow(game, game->x, game->y, floor, dark);
            if(dark < 1 && game->y % 4 == 0)
                dark += 0.03;
            if(dark > 1)
                dark = 1;
        }
        game->y++;
    }
}


void    shadow(t_game *game, int x, int y, int color, float darknessFactor)
{
    char *dst;

    int pixel_index = (y * game->line_length) + (x * game->bits_per_pixel / 8);
    int red = color >> 16 & 0xFF;
    int green = color >> 8 & 0xFF;
    int blue = color & 0xFF;
    red = (int)(red * darknessFactor);
    green = (int)(green * darknessFactor);
    blue = (int)(blue * darknessFactor);

    dst = game->addr + pixel_index;
    int darkenedColor = (red << 16) | (green << 8) | blue;
    *(unsigned int*)dst = darkenedColor;
}

void    shut_rays(t_game *game, t_map *map)
{
    int color;
    double x = ((double)game->xplayer / SIZE) * 10;
    double xp = MINI_WIDTH / 2;
    double yp = MINI_HEIGHT / 2;
    double y = ((double)game->yplayer / SIZE) * 10;
    double pix ;
    game->x = 0;
    game->rayangle = -PI / 6;
    while (game->rayangle <= PI / 6 && game->x < WIDTH)
    {
        pix = 0.0;
        color = 15790080;
        while(pix <= 50 && check_rays_2D(game, map, pix, x, y))
        {
            my_mlx_pixel_put(game, (xp + (cos(game->rotatangle + game->rayangle) * pix)),
            (yp + (sin(game->rotatangle + game->rayangle) * pix)), color);
            pix++;
        }
        game->rayangle += game->rotatspeed;
        game->x++;
    }
}

void init_distence(t_game *game, int pix)
{
    double angle;

    angle  = fabs(game->rayangle);
    game->distance = pix;
    if ((game->rayangle) < PI / 2)
        game->new_distance = game->distance * cos(angle);
    else
        game->new_distance = game->distance * cos(PI - (angle));
    game->distance = game->new_distance;
    game->projectedWallHeight = (SIZE * WIDTH) / game->distance;
}

void   render_3d(t_game *game, t_map *map)
{
	game->distance = 0;
	double pix ;
    game->rayangle = (-1 * PI) / 6;
	game->x = 0;

	while (game->rayangle <= PI / 6 && game->x < WIDTH)
	{
		pix = 0.0;
		while(pix < 1000 && check_rays_3D(game, map, pix))
			pix++;
        init_distence(game, pix);
        if (roundf(fmod(game->xplayer + (cos(game->rotatangle + game->rayangle) * (pix)), SIZE)) == 0)
		    game->virti = 0;
	    else if (roundf(fmod(game->yplayer + (sin(game->rotatangle + game->rayangle) * (pix)), SIZE)) == 0)
		    game->virti = 1;
		print_wall(game, game->xplayer + (cos(game->rotatangle + game->rayangle) * (pix)), game->yplayer + (sin(game->rotatangle + game->rayangle) * (pix)), pix);
		game->rayangle += game->rotatspeed;
		game->x++;
	}
}
