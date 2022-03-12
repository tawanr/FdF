/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:32:14 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/12 10:04:34 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->llen + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map	*map;
	//t_vertex	*temp;
	//t_maprow	*temprow;
	int		fd;
	t_vertex	***interpolated_arr;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		return (-1);
	map = parsemap(fd);
	/*
	temprow = map->maprow;
	printf("map parsed\n");
	while (temprow != NULL)
	{
		temp = temprow->firstvtx;
		while (temp != NULL)
		{
			printf("[%+06.2f][%+06.2f] ", temp->x, temp->y);
			temp = temp->next;
		}
		temprow = temprow->next;
		printf("\n");
	}
	*/
	//printf("map width: %i height: %i\n", map->width, map->height);
	mlx = mlx_init();
	//printf("init\n");
	mlx_win = mlx_new_window(mlx, 800, 600, "FdF");
	img.img = mlx_new_image(mlx, 800, 600);
	interpolated_arr = interpolatemap(map, 800, 600, 50);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.endian);
	drawmap(interpolated_arr, map->width, map->height, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (1);
}

void	getmapheight(int *mapheight, t_vertex ***map, int width, int height)
{
	int	i;
	int	j;

	mapheight[0] = map[0][0]->z;
	mapheight[1] = map[0][0]->z;
	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			if (map[i][j]->z < mapheight[0])
				mapheight[0] = map[i][j]->z;
			if (map[i][j]->z > mapheight[1])
				mapheight[1] = map[i][j]->z;
			j++;
		}
		i++;
	}
	mapheight[2] = mapheight[1] - mapheight[0];
	return ;
}

void	drawmap(t_vertex ***map, int width, int height, t_data *img)
{
	int		i;
	int		j;
	t_line	*curline;
	int		padding[2];
	int		mapheight[3];

	i = -1;
	padding[0] = (800 / (width + 2)) * 2 + 100;
	padding[1] = (600 / (height + 2)) * 2 + 150;
	getmapheight(&(*mapheight), map, width, height);
	while (++i < width)
	{
		j = -1;
		while (++j < height)
		{
			if (j != height - 1)
				curline = newline(map[i][j], map[i][j + 1]);
			if (j != height - 1)
				putline(curline, img, padding, mapheight);
			if (i != width - 1)
				curline = newline(map[i][j], map[i + 1][j]);
			if (i != width - 1)
				putline(curline, img, padding, mapheight);
		}
	}
}

t_vertex	***interpolatemap(t_map *map, int w_width, int w_height, int pad)
{
	double		factor;
	t_vertex	*tmp;
	t_maprow	*temprow;
	t_vertex	***int_map;
	int			i;
	int			j;

	i = 0;
	j = 0;
	int_map = (t_vertex ***)malloc(map->width * sizeof(t_vertex **));
	while (i < map->width)
		int_map[i++] = (t_vertex **)malloc(map->height * sizeof(t_vertex *));
	w_width = w_width - (2 * pad);
	w_height = w_height - (2 * pad);
	factor = w_width / map->width;
	if (w_height / map->height < factor)
		factor = w_height / map->height;
	rotatemap(map, 45);
	/*
	printf("map rotated\n");
	temprow = map->maprow;
	while (temprow != NULL)
	{
		tmp = temprow->firstvtx;
		while (tmp != NULL)
		{
			printf("[%+06.2f][%+06.2f] ", tmp->x, tmp->y);
			tmp = tmp->next;
		}
		temprow = temprow->next;
		printf("\n");
	}
	printf("interpolating with factor: %f\n", factor);
	*/
	temprow = map->maprow;
	while (temprow)
	{
		i = 0;
		tmp = temprow->firstvtx;
		while (tmp != NULL)
		{
			int_map[i][j] = getvert(tmp->x, tmp->y, tmp->z, factor);
			tmp = tmp->next;
			//printf("[%+08.2f][%+08.2f] ", int_map[i][j]->x, int_map[i][j]->y);
			i++;
		}
		//printf("\n");
		temprow = temprow->next;
		j++;
	}
	return (int_map);
}

void	rotatemap(t_map *map, double deg)
{
	double		o_x;
	double		o_y;
	t_maprow	*trow;
	t_vertex	*tmp;
	double		temp_x;

	deg = (deg * PI) / 180;
	o_x = ((double)map->width - 1) / 2;
	o_y = ((double)map->height - 1) / 2;
	trow = map->maprow;
	while (trow)
	{
		tmp = trow->firstvtx;
		while (tmp)
		{
			temp_x = (cos(deg) * (tmp->x - o_x)) + (sin(deg) * (tmp->y - o_y));
			temp_x += o_x;
			tmp->y = -(sin(deg) * (tmp->x - o_x)) + (cos(deg) * (tmp->y - o_y));
			tmp->x += o_y;
			tmp->x = temp_x;
			tmp = tmp->next;
		}
		trow = trow->next;
	}
	return ;
}


t_vertex	*getvert(double x, double y, double z, double factor)
{
	t_vertex	*newvert;
	double		z_factor;
	double		ele_factor;

	factor *= .8;
	ele_factor = .3;
	z_factor = sin((0 * PI) / 180) / sin((45 * PI) / 180);
	newvert = (t_vertex *)malloc(sizeof(t_vertex));
	newvert->x = round(x * factor);
	newvert->y = round((y - (z * ele_factor)) * (z_factor * factor));
	newvert->z = round(z * (z_factor * factor));
	newvert->next = NULL;
	return (newvert);
}

int	putline(t_line *line, t_data *img, int *padding, int *mapheight)
{
	double	cur_x;
	double	cur_y;
	double	cur_z;
	int		i;
	int		linelen;

	i = 0;
	linelen = ft_abs(ft_getmax(line->len_x, line->len_y));
	while (i < linelen)
	{
		cur_x = round((double)(line->len_x * i / linelen));
		cur_y = round((double)(line->len_y * i / linelen));
		cur_x += padding[0] + line->vertex1->x;
		cur_y += padding[1] + line->vertex1->y;
		cur_z = line->vertex1->z;
		cur_z += (double)((line->vertex2->z - line->vertex1->z) * i / linelen);
		if (!(cur_x >= 800 || cur_x < 0 || cur_y >= 600 || cur_y < 0))
			pixel_put(img, (int)cur_x, (int)cur_y, getcolor(cur_z, mapheight));
		i++;
	}
	return (1);
}

int	getcolor(double cur_z, int *maph)
{
	double	reheight;
	int		output;

	if (cur_z < (maph[2] / 3) + maph[0])
	{
		reheight = (double)((cur_z - maph[0]) / (maph[2] / 3));
		output = 0xFFFF00 | (int)round((((1 - reheight) * (double)0xFF)));
		return (output);
	}
	else if (cur_z < (maph[2] / 3 * 2) + maph[0])
	{
		reheight = ((cur_z - maph[0]) - (maph[2] / 3)) / (maph[2] / 3);
		return (0xFF0000 | ((int)(((1 - reheight) * (double)0xFF)) << 8));
	}
	else
	{
		reheight = ((cur_z - maph[0]) - (maph[2] / 3 * 2)) / (maph[2] / 3);
		if (cur_z == maph[1])
			reheight = 1;
		return (0xFF0000 | (int)((reheight * (double)0xFF)));
	}
	return (0xFFFFFF);
}

t_line	*newline(t_vertex *vertex1, t_vertex *vertex2)
{
	t_line	*output;

	output = (t_line *)malloc(sizeof(t_line));
	output->vertex1 = vertex1;
	output->vertex2 = vertex2;
	output->len_x = vertex2->x - vertex1->x;
	output->len_y = vertex2->y - vertex1->y;
	//printf("len_x: %i len_y: %i\n", output->len_x, output->len_y);
	return (output);
}

int	ft_getmax(int num1, int num2)
{
	if (ft_abs(num1) > ft_abs(num2))
		return (num1);
	return (num2);
}
