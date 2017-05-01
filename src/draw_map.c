/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 14:46:31 by liabanzh          #+#    #+#             */
/*   Updated: 2017/01/24 14:46:32 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	print_line(t_read current, t_read next, t_mlx *list, t_point *points)
{
	int color;

	if (current.z == list->level && next.z == list->level)
		color = 0x00994C00;
	else if (current.color == 0x00000000)
		color = 0x00505050;
	else
		color = current.color;
	next.z += (next.z != list->level) ? list->new_z : 0;
	current.z += (current.z != list->level) ? list->new_z : 0;
	math_points(list, &current, &next);
	points->x0 = (current.x - current.y) + list->win_x;
	points->y0 = ((current.x + current.y) / 2 + current.z) + list->win_y;
	points->x1 = (next.x - next.y) + list->win_x;
	points->y1 = ((next.x + next.y) / 2 + next.z) + list->win_y;
	inc(points, current, next);
	draw_line(list, points, color);
}

void	draw_point(t_read **map, t_mlx *list)
{
	t_point	*points;
	int		i;
	int		j;

	i = 0;
	points = (t_point*)malloc(sizeof(t_point));
	while (i < list->size_y)
	{
		j = 0;
		while (j < list->size_x)
		{
			if (j < list->size_x - 1)
				print_line(map[i][j], map[i][j + 1], list, points);
			if (i < list->size_y - 1)
				print_line(map[i][j], map[i + 1][j], list, points);
			if (j < list->size_x - 1 && i < list->size_y - 1 &&
				list->paralel == 1)
				print_line(map[i][j], map[i + 1][j + 1], list, points);
			j++;
		}
		i++;
	}
}

int		map_iter(t_read **map, t_mlx *list, int i, int j)
{
	int res;
	int max;

	max = 0;
	res = map[i][j].z;
	while (i < list->size_y)
	{
		j = 0;
		while (j < list->size_x)
		{
			if (map[i][j].z == res)
				max++;
			j++;
		}
		i++;
	}
	return (max);
}

int		level(t_read **map, t_mlx *list)
{
	int i;
	int j;
	int max;
	int curr;
	int res;

	i = 0;
	max = map_iter(map, list, 0, 0);
	res = map[0][0].z;
	while (i < list->size_y)
	{
		j = 0;
		while (j < list->size_x)
		{
			curr = map_iter(map, list, i, j);
			if (curr > max)
			{
				max = curr;
				res = map[i][j].z;
			}
			j++;
		}
		i++;
	}
	return (res);
}

void	draw_map(t_read **map, t_mlx *list)
{
	list->zoom = SIZE_X / sqrt(pow((map[0][list->size_x - 1].x -
		map[0][list->size_x - 1].y) - (map[list->size_y - 1][0].x -
		map[list->size_y - 1][0].y), 2) + pow(((map[0][list->size_x - 1].x +
			map[0][list->size_x - 1].y) / 2 + map[0][list->size_x - 1].z) -
		((map[list->size_y - 1][0].x + map[list->size_y - 1][0].y) / 2 +
			map[list->size_y - 1][0].z), 2));
	if (list->zoom < 1)
		list->zoom = 1;
	list->map = map;
	list->paralel = 0;
	list->level = 0;
	list->angle_x = 0;
	list->angle_y = 0;
	list->angle_z = 0;
	list->cosx = cos(0);
	list->sinx = sin(0);
	list->cosy = cos(0);
	list->siny = sin(0);
	list->cosz = cos(0);
	list->sinz = sin(0);
	draw_point(map, list);
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	mlx_key_hook(list->win, on_key, list);
	mlx_mouse_hook(list->win, on_mouse, list);
	mlx_loop(list->mlx);
}
