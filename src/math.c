/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 14:43:37 by liabanzh          #+#    #+#             */
/*   Updated: 2017/02/08 14:43:38 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	next_next(t_mlx *list, t_read *next)
{
	int	tmp;

	tmp = next->y;
	next->y = rounding(next->y * list->cosx * list->zoom) -
				rounding(next->z * list->sinx * list->zoom);
	next->z = rounding(tmp * list->sinx * list->zoom) +
				rounding(next->z * list->cosx * list->zoom);
	next->x *= list->zoom;
	tmp = next->x;
	next->x = rounding(next->x * list->cosy) - rounding(next->z * list->siny);
	next->z = rounding(tmp * list->siny) + rounding(next->z * list->cosy);
	tmp = next->x;
	next->x = rounding(next->x * list->cosz) - rounding(next->y * list->sinz);
	next->y = rounding(tmp * list->sinz) + rounding(next->y * list->cosz);
}

void	math_points(t_mlx *list, t_read *current, t_read *next)
{
	int tmp;

	tmp = current->y;
	current->y = rounding(current->y * list->cosx * list->zoom) -
				rounding(current->z * list->sinx * list->zoom);
	current->z = rounding(tmp * list->sinx * list->zoom) +
				rounding(current->z * list->cosx * list->zoom);
	current->x *= list->zoom;
	tmp = current->x;
	current->x = rounding(current->x * list->cosy) -
				rounding(current->z * list->siny);
	current->z = rounding(tmp * list->siny) + rounding(current->z * list->cosy);
	tmp = current->x;
	current->x = rounding(current->x * list->cosz) -
				rounding(current->y * list->sinz);
	current->y = rounding(tmp * list->sinz) + rounding(current->y * list->cosz);
	next_next(list, next);
}

int		loop_z(t_mlx *list)
{
	if (list->flag2 == 1)
	{
		clear_window(list);
		list->angle_x += 0.1;
		list->sinx = sin(list->angle_x);
		list->cosx = cos(list->angle_x);
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	return (1);
}

int		loop_x(t_mlx *list)
{
	if (list->flag1 == 1)
	{
		clear_window(list);
		list->angle_z += 0.05;
		list->sinz = sin(list->angle_z);
		list->cosz = cos(list->angle_z);
		draw_point(list->map, list);
		mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	}
	return (1);
}

void	clear_window(t_mlx *list)
{
	mlx_destroy_image(list->mlx, list->img_ptr);
	list->img_ptr = mlx_new_image(list->mlx, SIZE_X, SIZE_Y);
	list->img = mlx_get_data_addr(list->img_ptr,
		&(list->pixel_size), &(list->line_size), &(list->endian));
}
