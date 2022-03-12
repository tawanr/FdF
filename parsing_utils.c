/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:51:32 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/13 02:38:24 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	appvertex(t_maprow *maprow, int column, int elevation, int color)
{
	t_vertex	*newvertex;
	t_vertex	*temp;

	newvertex = (t_vertex *)malloc(sizeof(t_vertex));
	if (!newvertex)
		return (0);
	newvertex->x = column;
	newvertex->y = maprow->height;
	newvertex->z = elevation;
	newvertex->color = color;
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

int	ft_ishex(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= 'f')
		return (1);
	else if (c >= 'A' && c <= 'F')
		return (1);
	return (0);
}
