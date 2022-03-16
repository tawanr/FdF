/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:32:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/16 14:44:26 by tratanat         ###   ########.fr       */
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
# define WIDTH 1600
# define HEIGHT 900

typedef struct s_vertex
{
	double			x;
	double			y;
	double			z;
	struct s_vertex	*next;
	int				color;
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
	int				height;
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
	t_map		*parsemap;
	double		zoomfactor;
	int			z_angle;
	int			w_width;
	int			w_height;
	double		m_width;
	double		m_height;
	int			shift_x;
	int			shift_y;
	double		ele_factor;
	int			customcolor;
	int			rotateangle;
	void		*mlx;
	void		*mlx_win;
	t_data		*img;
	int			mouse_pressed;
	int			rmouse_pressed;
	int			mouse_x;
	int			mouse_y;
	int			def_shf_x;
	int			def_shf_y;
	int			def_zoom;
}	t_fdfvars;

void		pixel_put(t_data *data, int x, int y, int color);
void		putline(t_line *line, t_data *img, t_fdfvars *fdfvars, int *ele);
int			ft_getmax(int num1, int num2);
t_line		*newline(t_vertex *vertex1, t_vertex *vertex2);
t_map		*parsemap(int fd);
t_maprow	*getmaprow(int row, char **readrow);
int			appvertex(t_maprow *maprow, int row, int elevation, int color);
int			checkcolor(char *str);
int			appendrow(t_map *map, t_maprow *newrow);
int			findmapwidth(t_map *map);
void		drawmap(t_fdfvars *fdfvars, t_data *img);
t_vertex	***interpolatemap(t_fdfvars *fdfvars);
t_vertex	*getvert(t_vertex *src, t_fdfvars *fdfvars);
void		rotatemap(t_vertex ***int_map, t_map *map, double deg);
int			getcolor(double cur_z, int *maph);
void		init_vars(t_fdfvars *fdfvars);
int			getlncolor(int i, int linelen, t_line *line);
int			getcustcol(double cur_z, int *maph);
void		getdrawdim(t_fdfvars *fdfvars, t_vertex ***int_map);
double		getdrawheight(t_fdfvars *fdfvars, t_vertex ***int_map);
void		initpadding(t_fdfvars *fdfvars);
int			keymod(int keycode, t_fdfvars *fdfvars);
void		init_mlx(t_fdfvars *fdfvars, void *mlx, void *mlx_win, t_data *img);
int			drawframe(t_fdfvars *fdfvars);
int			mousectl(int button, int x, int y, t_fdfvars *fdfvars);
int			end_win(t_fdfvars *fdfvars);
int			mouserot(int x, int y, t_fdfvars *fdfvars);
int			mouserel(int button, int x, int y, t_fdfvars *fdfvars);
void		inithooks(void *mlx_win, t_fdfvars *fdfvars);
void		freearr(t_fdfvars *fdfvars, int fullflag);
void		int_vertex(t_vertex *ver, t_vertex *tmp, double deg, double xy[2]);
int			ft_ishex(char c);
void		keycont(int keycode, t_fdfvars *fdfvars);
void		init_arr(t_fdfvars *fdfvars);
void		clean_mlx(t_fdfvars *fdfvars);

#endif