/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:52:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/16 14:39:12 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

t_map	*parsemap(int fd)
{
	char	*curline;
	int		rows;
	t_map	*map;

	rows = 0;
	map = (t_map *)malloc(sizeof(t_map));
	map->maprow = NULL;
	curline = get_next_line(fd);
	while (curline)
	{
		appendrow(map, getmaprow(rows, ft_split(curline, ' ')));
		free(curline);
		curline = get_next_line(fd);
		rows++;
	}
	free(curline);
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
	int			color;

	maprow = (t_maprow *)malloc(sizeof(t_maprow));
	maprow->firstvtx = NULL;
	maprow->next = NULL;
	maprow->height = row;
	column = 0;
	while (readrow[column])
	{
		elevation = ft_atoi(readrow[column]);
		color = checkcolor(readrow[column] + getdigit(elevation));
		if (!appvertex(maprow, column, elevation, color))
			return (NULL);
		column++;
	}
	while (column >= 0)
		free(readrow[column--]);
	free(readrow);
	return (maprow);
}

int	checkcolor(char *str)
{
	int	i;
	int	colornum;

	colornum = 0;
	if (!ft_strncmp(str, ",0x", 3))
		str += 3;
	while (ft_ishex(*str))
	{
		colornum = colornum << 8;
		i = 0;
		while (i < 2)
		{
			if (str[i] - '0' <= 9)
				colornum += (str[i] - '0') * ((16 * !i) + !i);
			else if (str[i] >= 'a' && str[i] <= 'f')
				colornum += (10 + (str[i] - 'a')) * ((16 * !i) + !i);
			else if (str[i] >= 'A' && str[i] <= 'F')
				colornum += (10 + (str[i] - 'A')) * ((16 * !i) + !i);
			i++;
		}
		str += 2;
	}
	if (colornum == 0)
		colornum = 0x00FFFFFFF;
	return (colornum);
}
