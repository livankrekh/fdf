/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 17:50:17 by liabanzh          #+#    #+#             */
/*   Updated: 2017/02/11 17:50:21 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void			on_key5(int keycode, t_mlx *list)
{
	if (keycode == 0)
	{
		clear_window(list);
		list->angle_z -= 0.1;
		list->sinz = sin(list->angle_z);
		list->cosz = cos(list->angle_z);
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	if (keycode == 2)
	{
		clear_window(list);
		list->angle_z += 0.1;
		list->sinz = sin(list->angle_z);
		list->cosz = cos(list->angle_z);
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
}

void			inc(t_point *points, t_read current, t_read next)
{
	points->q = rounding(sqrt(pow(points->x1 - points->x0, 2) +
		pow(points->y1 - points->y0, 2)));
	points->red0 = current.color >> 16;
	points->green0 = ((current.color >> 8) & (current.color >> 16));
	points->blue0 = current.color & (current.color >> 16);
	points->delta_red = (next.color >> 16) - points->red0;
	points->delta_green = ((next.color >> 8) &
		(next.color >> 16)) - points->green0;
	points->delta_blue = (next.color & (next.color >> 16)) - points->blue0;
	points->index = 0;
}

void			on_mouse_hook(int code, int x, int y, t_mlx *list)
{
	if (code == 1)
	{
		clear_window(list);
		list->win_x = x;
		list->win_y = y;
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
}
