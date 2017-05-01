/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 14:56:53 by liabanzh          #+#    #+#             */
/*   Updated: 2017/01/21 14:56:54 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <mlx.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# define SIZE_Y 1000
# define SIZE_X 1000

typedef struct	s_bresenh
{
	int			deltax;
	int			deltay;
	int			signx;
	int			signy;
	int			error;
	int			error2;
}				t_bresenh;

typedef	struct	s_read
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_read;

typedef struct	s_point
{
	int			x0;
	int			x1;
	int			y0;
	int			y1;
	int			delta_red;
	int			delta_green;
	int			delta_blue;
	int			red0;
	int			green0;
	int			blue0;
	int			deltax;
	int			deltay;
	int			signx;
	int			signy;
	int			index;
	int			q;
}				t_point;

typedef	struct	s_mlx
{
	void		*win;
	void		*mlx;
	void		*img_ptr;
	char		*img;
	int			line_size;
	int			pixel_size;
	int			size_y;
	int			size_x;
	int			zoom;
	int			endian;
	t_read		**map;
	int			new_z;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	float		sinx;
	float		siny;
	float		sinz;
	float		cosx;
	float		cosy;
	float		cosz;
	int			win_x;
	int			win_y;
	int			paralel;
	int			level;
	int			flag1;
	int			flag2;
}				t_mlx;

void			math_points(t_mlx *list, t_read *current, t_read *next);
void			draw_line(t_mlx *list, t_point *points, int color1);
void			draw_map(t_read **map, t_mlx *list);
void			zoom(t_mlx *list, t_read **map);
void			include_pixel(int x, int y, t_mlx *list, int color);
int				rounding(float x);
void			draw_point(t_read **map, t_mlx *list);
int				on_key(int keycode, t_mlx *list);
int				on_mouse(int code, int x, int y, t_mlx *list);
int				level(t_read **map, t_mlx *list);
void			clear_window(t_mlx *list);
int				loop_x(t_mlx *list);
int				loop_z(t_mlx *list);
void			on_key5(int keycode, t_mlx *list);
void			inc(t_point *points, t_read current, t_read next);
void			on_mouse_hook(int code, int x, int y, t_mlx *list);

#endif
