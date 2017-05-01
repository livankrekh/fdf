/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 17:12:49 by liabanzh          #+#    #+#             */
/*   Updated: 2017/01/22 17:12:50 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int				rounding(float x)
{
	return (x - (int)x >= 0.5 ? (int)x + 1 : (int)x);
}

void			include_value(t_bresenh *br, t_point *points)
{
	br->deltax = abs(points->x1 - points->x0);
	br->deltay = abs(points->y1 - points->y0);
	br->signx = points->x0 < points->x1 ? 1 : -1;
	br->signy = points->y0 < points->y1 ? 1 : -1;
	br->error = br->deltax - br->deltay;
}

void			include_pixel(int x, int y, t_mlx *list, int color)
{
	void	*tmp;

	if ((x >= SIZE_X || y >= SIZE_Y) || (x < 0 || y < 0))
		return ;
	tmp = list->img;
	tmp += (list->line_size * y) + (x * 4);
	ft_memcpy(tmp, &color, 4);
}

int				gradient(t_point *points, int i, int color1, t_bresenh *br)
{
	int new_r;
	int new_b;
	int new_g;

	new_r = 0;
	new_g = 0;
	new_b = 0;
	if (points->delta_red == 0 && points->delta_green == 0
		&& points->delta_blue == 0)
		return (color1);
	if (br->deltax >= br->deltay && br->deltax != 0)
	{
		new_r = rounding(points->delta_red / br->deltax);
		new_b = rounding(points->delta_blue / br->deltax);
		new_g = rounding(points->delta_green / br->deltax);
	}
	else if (br->deltax < br->deltay && br->deltay != 0)
	{
		new_r = rounding(points->delta_red / br->deltay);
		new_b = rounding(points->delta_blue / br->deltay);
		new_g = rounding(points->delta_green / br->deltay);
	}
	return ((((new_r * i) + points->red0) * 255 * 255) + (((new_g * i) +
		points->green0) * 255) + ((new_b * i) + points->blue0));
}

void			draw_line(t_mlx *list, t_point *points, int color1)
{
	int			x;
	int			y;
	t_bresenh	*br;

	br = (t_bresenh*)malloc(sizeof(t_bresenh));
	include_value(br, points);
	x = points->x0;
	y = points->y0;
	include_pixel(points->x1, points->y1, list, color1);
	while ((x != points->x1 || y != points->y1) && (x < SIZE_X || y < SIZE_Y))
	{
		points->index++;
		include_pixel(x, y, list, gradient(points, points->index, color1, br));
		br->error2 = br->error * 2;
		if (br->error2 * 2 > br->deltay * (-1))
		{
			br->error -= br->deltay;
			x += br->signx;
		}
		if (br->error2 * 2 < br->deltax)
		{
			br->error += br->deltax;
			y += br->signy;
		}
	}
}
