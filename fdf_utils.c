/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:53:30 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/14 17:22:49 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

t_line	*newline(t_vertex *vertex1, t_vertex *vertex2)
{
	t_line	*output;

	output = (t_line *)malloc(sizeof(t_line));
	output->vertex1 = vertex1;
	output->vertex2 = vertex2;
	output->len_x = vertex2->x - vertex1->x;
	output->len_y = vertex2->y - vertex1->y;
	return (output);
}

int	ft_getmax(int num1, int num2)
{
	if (ft_abs(num1) > ft_abs(num2))
		return (num1);
	return (num2);
}

t_vertex	*getvert(t_vertex *src, t_fdfvars *fdfvars)
{
	double		z_factor;
	double		y_factor;
	double		factor;
	double		ele;
	double		max_z;

	factor = fdfvars->zoomfactor;
	ele = fdfvars->ele_factor;
	z_factor = sin((fdfvars->z_angle * PI) / 180) / sin((45 * PI) / 180);
	y_factor = sin((fdfvars->z_angle * PI) / 180) / sin((45 * PI) / 180);
	max_z = sin(0.5 * PI) / sin((45 * PI) / 180);
	src->x = round(src->x * factor);
	if (y_factor > 1)
		y_factor = 1;
	src->y = round((src->y) * (y_factor * factor));
	src->y -= (src->z * factor * ele * ((max_z - z_factor) / max_z));
	src->z = round(src->z * (factor + !z_factor));
	src->next = NULL;
	return (src);
}

void	putline(t_line *line, t_data *img, t_fdfvars *fdfvars, int *ele)
{
	double	x;
	double	y;
	double	z;
	int		i;
	int		linelen;

	i = -1;
	linelen = ft_abs(ft_getmax(line->len_x, line->len_y));
	while (++i < linelen)
	{
		x = round((double)(line->len_x * i / linelen));
		y = round((double)(line->len_y * i / linelen));
		x += fdfvars->shift_x + line->vertex1->x;
		y += fdfvars->shift_y + line->vertex1->y;
		z = line->vertex1->z;
		z += (double)((line->vertex2->z - line->vertex1->z) * i / linelen);
		if (!(x >= WIDTH || x < 0 || y >= HEIGHT || y < 0))
		{
			if (fdfvars->customcolor)
				pixel_put(img, (int)x, (int)y, getcustcol(z, ele));
			else
				pixel_put(img, (int)x, (int)y, getlncolor(i, linelen, line));
		}
	}
	free(line);
}

double	getdrawheight(t_fdfvars *fdfvars, t_vertex ***int_map)
{
	int		i;
	int		j;
	double	drawheight[2];

	i = 0;
	drawheight[0] = int_map[0][0]->y;
	drawheight[1] = int_map[0][0]->y;
	while (i < fdfvars->parsemap->width)
	{
		j = 0;
		while (j < fdfvars->parsemap->height)
		{
			if (int_map[i][j]->y < drawheight[0])
				drawheight[0] = int_map[i][j]->y;
			else if (int_map[i][j]->y > drawheight[1])
				drawheight[1] = int_map[i][j]->y;
			j++;
		}
		i++;
	}
	if (drawheight[0] < 0)
		fdfvars->shift_y = -drawheight[0];
	return (drawheight[1] - drawheight[0]);
}
