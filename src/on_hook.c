/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:51:40 by liabanzh          #+#    #+#             */
/*   Updated: 2017/01/30 16:51:42 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void			on_key4(int keycode, t_mlx *list)
{
	if (keycode == 125)
	{
		list->flag2 = 1;
		loop_z(list);
		list->flag2 = 0;
	}
	if (keycode == 126)
	{
		clear_window(list);
		list->angle_x -= 0.1;
		list->sinx = sin(list->angle_x);
		list->cosx = cos(list->angle_x);
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	if (keycode == 49)
	{
		list->flag1 = (list->flag1 == 0) ? 1 : 0;
		mlx_loop_hook(list->mlx, loop_x, list);
	}
	if (keycode == 36)
	{
		list->flag2 = (list->flag2 == 0) ? 1 : 0;
		mlx_loop_hook(list->mlx, loop_z, list);
	}
}

void			on_key3(int keycode, t_mlx *list)
{
	if (keycode == 117)
	{
		clear_window(list);
		list->new_z = 0;
		list->level = 0;
		list->angle_x = 0;
		list->angle_y = 0;
		list->angle_z = 0;
		list->sinx = sin(0);
		list->cosx = cos(0);
		list->siny = sin(0);
		list->cosy = cos(0);
		list->sinz = sin(0);
		list->cosz = cos(0);
		list->paralel = 0;
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	if (keycode == 48)
	{
		clear_window(list);
		list->paralel = (list->paralel == 0) ? 1 : 0;
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
}

void			on_key2(int keycode, t_mlx *list)
{
	if (keycode == 123)
	{
		clear_window(list);
		list->angle_y -= 0.1;
		list->siny = sin(list->angle_y);
		list->cosy = cos(list->angle_y);
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	if (keycode == 124)
	{
		clear_window(list);
		list->angle_y += 0.1;
		list->siny = sin(list->angle_y);
		list->cosy = cos(list->angle_y);
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	on_key3(keycode, list);
	on_key4(keycode, list);
	on_key5(keycode, list);
}

int				on_key(int keycode, t_mlx *list)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 1 || keycode == 13)
	{
		clear_window(list);
		if (keycode == 1)
			list->new_z += 1;
		if (keycode == 13)
			list->new_z -= 1;
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	if (keycode == 37)
	{
		clear_window(list);
		list->level = level(list->map, list);
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	on_key2(keycode, list);
	return (0);
}

int				on_mouse(int code, int x, int y, t_mlx *list)
{
	if (code == 4)
	{
		clear_window(list);
		list->zoom += 1;
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	if (code == 5)
	{
		if (list->zoom > 1)
		{
			clear_window(list);
			list->zoom -= 1;
			draw_point(list->map, list);
			mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
		}
	}
	on_mouse_hook(code, x, y, list);
	return (0);
}
