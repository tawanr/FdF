/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:52:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/08 20:42:20 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

t_map	*parsemap(int fd)
{
	char	*curline;
	int		offset;
	int		rows;
	t_map	*map;

	offset = 0;
	rows = 0;
	map = (t_map *)malloc(sizeof(t_map));
	map->maprow = NULL;
	curline = get_next_line(fd);
	while (curline)
	{
		appendrow(map, getmaprow(rows, ft_split(curline, ' ')));
		curline = get_next_line(fd);
		rows++;
	}
	map->height = rows;
	map->width = findmapwidth(map);
	return (map);
}

int	findmapwidth(t_map *map)
{
	int			width;
	t_vertex	*temp;

	width = 0;
	temp = map->maprow->firstvtx;
	while (temp != NULL)
	{
		width++;
		temp = temp->next;
	}
	return (width);
}

int	appendrow(t_map *map, t_maprow *newrow)
{
	t_maprow	*temp;

	temp = map->maprow;
	if (temp == NULL)
		map->maprow = newrow;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newrow;
	}
	return (1);
}

t_maprow	*getmaprow(int row, char **readrow)
{
	t_maprow	*maprow;
	int			column;
	int			elevation;
	t_vertex	*temp;

	maprow = (t_maprow *)malloc(sizeof(t_maprow));
	maprow->firstvtx = NULL;
	maprow->next = NULL;
	column = 0;
	while (readrow[column])
	{
		temp = maprow->firstvtx;
		elevation = ft_atoi(readrow[column]);
		if (!appvertex(maprow, column, row, elevation))
			return (NULL);
		column++;
	}
	while (column >= 0)
		free(readrow[column--]);
	free(readrow);
	return (maprow);
}

int	appvertex(t_maprow *maprow, int column, int row, int elevation)
{
	t_vertex	*newvertex;
	t_vertex	*temp;

	newvertex = (t_vertex *)malloc(sizeof(t_vertex));
	if (!newvertex)
		return (0);
	newvertex->x = column;
	newvertex->y = row;
	newvertex->z = elevation;
	newvertex->next = NULL;
	temp = maprow->firstvtx;
	if (temp == NULL)
		maprow->firstvtx = newvertex;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newvertex;
	}
	return (1);
}
