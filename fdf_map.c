/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:56:09 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/16 14:44:42 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

t_vertex	***interpolatemap(t_fdfvars *fdfvars)
{
	t_vertex	***int_map;
	int			i;
	int			j;

	j = 0;
	i = 0;
	int_map = fdfvars->arr_map;
	while (j < fdfvars->parsemap->height)
	{
		i = 0;
		while (i < fdfvars->parsemap->width)
		{
			int_map[i][j] = getvert(int_map[i][j], fdfvars);
			i++;
		}
		j++;
	}
	return (int_map);
}

void	rotatemap(t_vertex ***intm, t_map *map, double deg)
{
	double		xy[2];
	t_maprow	*trow;
	t_vertex	*tmp;
	int			j;

	deg = (deg * PI) / 180;
	xy[0] = ((double)map->width - 1) / 2;
	xy[1] = ((double)map->height - 1) / 2;
	trow = map->maprow;
	while (trow)
	{
		tmp = trow->firstvtx;
		j = 0;
		while (j < map->width)
		{
			int_vertex(intm[j][trow->height], tmp, deg, xy);
			j++;
			tmp = tmp->next;
		}
		trow = trow->next;
	}
	return ;
}

void	int_vertex(t_vertex *ver, t_vertex *tmp, double deg, double *xy)
{
	double	temp_x;

	temp_x = (cos(deg) * (tmp->x - xy[0]));
	temp_x += (sin(deg) * (tmp->y - xy[1])) + xy[1];
	ver->y = -(sin(deg) * (tmp->x - xy[0]));
	ver->y += (cos(deg) * (tmp->y - xy[1])) + xy[1];
	ver->x = temp_x;
	ver->z = tmp->z;
	ver->color = tmp->color;
}

void	getmapheight(int *mapheight, t_fdfvars *fdfvars)
{
	int			i;
	int			j;
	t_vertex	***map;

	map = fdfvars->arr_map;
	mapheight[0] = map[0][0]->z;
	mapheight[1] = map[0][0]->z;
	i = 0;
	while (i < fdfvars->parsemap->width)
	{
		j = 0;
		while (j < fdfvars->parsemap->height)
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

void	drawmap(t_fdfvars *fdfvars, t_data *img)
{
	int			i;
	int			j;
	t_line		*curline;
	int			mapheight[3];
	t_vertex	***map;

	i = -1;
	map = fdfvars->arr_map;
	getmapheight(&(*mapheight), fdfvars);
	while (++i < fdfvars->parsemap->width)
	{
		j = -1;
		while (++j < fdfvars->parsemap->height)
		{
			if (j != fdfvars->parsemap->height - 1)
				curline = newline(map[i][j], map[i][j + 1]);
			if (j != fdfvars->parsemap->height - 1)
				putline(curline, img, fdfvars, mapheight);
			if (i != fdfvars->parsemap->width - 1)
				curline = newline(map[i][j], map[i + 1][j]);
			if (i != fdfvars->parsemap->width - 1)
				putline(curline, img, fdfvars, mapheight);
		}
	}
}
