/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:32:14 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/16 14:43:56 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	int			fd;
	t_fdfvars	fdfvars;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		return (-1);
	fdfvars.parsemap = parsemap(fd);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "FdF");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	init_mlx(&fdfvars, mlx, mlx_win, &img);
	init_vars(&fdfvars);
	fdfvars.arr_map = interpolatemap(&fdfvars);
	initpadding(&fdfvars);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.endian);
	drawmap(&fdfvars, &img);
	inithooks(mlx_win, &fdfvars);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (1);
}

void	getdrawdim(t_fdfvars *fdfvars, t_vertex ***int_map)
{
	int		i;
	int		j;
	double	drawwidth[2];

	i = 0;
	drawwidth[0] = int_map[0][0]->x;
	drawwidth[1] = int_map[0][0]->x;
	while (i < fdfvars->parsemap->width)
	{
		j = 0;
		while (j < fdfvars->parsemap->height)
		{
			if (int_map[i][j]->x < drawwidth[0])
				drawwidth[0] = int_map[i][j]->x;
			else if (int_map[i][j]->x > drawwidth[1])
				drawwidth[1] = int_map[i][j]->x;
			j++;
		}
		i++;
	}
	fdfvars->m_width = drawwidth[1] - drawwidth[0];
	if (drawwidth[0] < 0)
		fdfvars->shift_x = -drawwidth[0];
	fdfvars->m_height = getdrawheight(fdfvars, int_map);
}

int	getlncolor(int i, int linelen, t_line *line)
{
	unsigned int	c[2];
	unsigned int	output;
	int				j;
	int				temp;

	output = 0;
	j = 0;
	c[0] = line->vertex1->color;
	c[1] = line->vertex2->color;
	if (c[0] == c[1])
		return (c[0]);
	while (j < 3)
	{
		temp = (((c[1] >> (8 * j)) & 0xFF) - ((c[0] >> (8 * j)) & 0xFF));
		temp = round((double)temp * i / linelen);
		temp = temp + ((c[0] >> (8 * j)) & 0xFF);
		if (temp > 0xFF)
			temp = 0xFF;
		output = output | (temp << (j * 8));
		j++;
	}
	return (output);
}

int	getcustcol(double cur_z, int *maph)
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
