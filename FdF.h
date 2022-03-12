/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:32:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/11 15:48:22 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# define PI 3.141592654

typedef struct s_vertex
{
	double			x;
	double			y;
	double			z;
	struct s_vertex	*next;
	int				vertcolor;
}	t_vertex;

typedef struct s_line
{
	t_vertex	*vertex1;
	t_vertex	*vertex2;
	int			len_x;
	int			len_y;
}	t_line;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
}	t_data;

typedef struct s_maprow
{
	t_vertex		*firstvtx;
	struct s_maprow	*next;
}	t_maprow;

typedef struct s_map
{
	t_maprow	*maprow;
	int			height;
	int			width;
}	t_map;

typedef struct s_todraw
{
	t_line		*linelst;
}	t_todraw;

typedef struct s_fdfvars
{
	t_todraw	drawmap;
	t_vertex	***arr_map;
	t_map		parsemap;
}	t_fdfvars;

void		pixel_put(t_data *data, int x, int y, int color);
int			putline(t_line *line, t_data *img, int *padup, int *mapheight);
int			ft_getmax(int num1, int num2);
t_line		*newline(t_vertex *vertex1, t_vertex *vertex2);
t_map		*parsemap(int fd);
t_maprow	*getmaprow(int row, char **readrow);
int			appvertex(t_maprow *maprow, int column, int row, int elevation);
int			appendrow(t_map *map, t_maprow *newrow);
int			findmapwidth(t_map *map);
void		drawmap(t_vertex ***map, int width, int height, t_data *img);
t_vertex	***interpolatemap(t_map *map, int w_width, int w_height, int pad);
t_vertex	*getvert(double x, double y, double z, double factor);
void		rotatemap(t_map *map, double deg);
int			getcolor(double cur_z, int *maph);

#endif