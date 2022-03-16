/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:59:31 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/16 11:44:21 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	end_win(t_fdfvars *fdfvars)
{
	t_maprow	*currow;
	t_vertex	*cur;
	t_maprow	*tmprow;
	t_vertex	*tmp;

	freearr(fdfvars, 1);
	currow = fdfvars->parsemap->maprow;
	while (currow)
	{
		cur = currow->firstvtx;
		while (cur)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
		tmprow = currow;
		currow = currow->next;
		free(tmprow);
	}
	free(fdfvars->parsemap);
	clean_mlx(fdfvars);
	return (1);
}

void	clean_mlx(t_fdfvars *fdfvars)
{
	mlx_destroy_image(fdfvars->mlx, fdfvars->img->img);
	mlx_clear_window(fdfvars->mlx, fdfvars->mlx_win);
	mlx_destroy_window(fdfvars->mlx, fdfvars->mlx_win);
	mlx_destroy_display(fdfvars->mlx);
	free(fdfvars->mlx);
	exit(1);
}

void	freearr(t_fdfvars *fdfvars, int fullflag)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdfvars->parsemap->width)
	{
		j = 0;
		while (j < fdfvars->parsemap->height)
			free(fdfvars->arr_map[i][j++]);
		if (fullflag == 1)
		{
			free(fdfvars->arr_map[i]);
		}
		i++;
	}
	if (fullflag == 1)
		free(fdfvars->arr_map);
}
