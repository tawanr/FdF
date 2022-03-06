/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:32:14 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/06 20:00:19 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
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
	t_vertex	*temp;
	t_maprow	*temprow;
	int		fd;
	t_vertex	***interpolated_arr;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		return (-1);
	map = parsemap(fd);
	temprow = map->maprow;
	while (temprow != NULL)
	{
		temp = temprow->firstvtx;
		while (temp != NULL)
		{
			printf("%i ", temp->z);
			temp = temp->next;
		}
		temprow = temprow->next;
		printf("\n");
	}
	printf("map width: %i height: %i\n", map->width, map->height);
	interpolated_arr = interpolatemap(map, 800, 600, 50);
	drawmap(interpolated_arr, map->width, map->height, &img);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "Hello world!");
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.endian);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (1);
}

void	drawmap(t_vertex ***map, int width, int height, t_data *img)
{
	int		i;
	int		j;
	t_line	*curline;

	i = 0;
	j = 0;
	while (i < width - 1)
	{
		while (j < height - 1)
		{
			curline = newline(map[i][j], map[i][j + 1]);
			putline(curline, img);
			j++;
		}
		j = 0;
		i++;
	}
	return ;
}

t_vertex	***interpolatemap(t_map *map, int w_width, int w_height, int pad)
{
	double		factor;
	t_vertex	*tmp;
	t_maprow	*temprow;
	t_vertex	***int_map;
	int			i;

	i = 0;
	int_map = (t_vertex ***)malloc(map->width * sizeof(t_vertex **));
	while (i < map->width)
		int_map[i++] = (t_vertex **)malloc(map->height * sizeof(t_vertex *));
	w_width = w_width - (2 * pad);
	w_height = w_height - (2 * pad);
	factor = w_width / map->width;
	if (w_height / map->height < factor)
		factor = w_height / map->height;
	temprow = map->maprow;
	while (temprow)
	{
		tmp = temprow->firstvtx;
		while (tmp != NULL)
		{
			int_map[tmp->x][tmp->y] = getvert(tmp->x, tmp->y, tmp->z, factor);
			tmp = tmp->next;
		}
		temprow = temprow->next;
	}
	return (int_map);
}

t_vertex	*getvert(int x, int y, int z, double factor)
{
	t_vertex	*newvert;

	newvert = (t_vertex *)malloc(sizeof(t_vertex));
	newvert->x = round(x * factor);
	newvert->y = round(y * factor);
	newvert->z = round(z * factor);
	newvert->next = NULL;
	return (newvert);
}

int	putline(t_line *line, t_data *img)
{
	double	cur_x;
	double	cur_y;
	int		i;
	int		linelen;

	i = 0;
	linelen = ft_getmax(line->len_x, line->len_y);
	while (i < linelen)
	{
		cur_x = line->vertex1->x + round((double)(line->len_x * i / linelen));
		cur_y = line->vertex1->y + round((double)(line->len_y * i / linelen));
		my_mlx_pixel_put(img, cur_x, cur_y, 0x00FF00);
		i++;
	}
	return (1);
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
	if (num1 > num2)
		return (num1);
	return (num2);
}
