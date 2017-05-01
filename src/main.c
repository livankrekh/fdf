/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: liabanzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 12:31:27 by liabanzh          #+#    #+#             */
/*   Updated: 2017/01/21 12:31:28 by liabanzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../get_next_line/get_next_line.h"

static	t_read	**struct_alloc(int size_y, int size_x, t_mlx *list)
{
	t_read	**map;
	int		i;

	i = 0;
	map = (t_read**)malloc(sizeof(t_read*) * size_y);
	while (i < size_y)
	{
		map[i] = (t_read*)malloc(sizeof(t_read) * size_x);
		i++;
	}
	list->win_x = SIZE_X / 2;
	list->win_y = SIZE_Y / 2;
	return (map);
}

static	t_read	include_var(int i, int j, char **split, t_mlx *list)
{
	t_read	elem;

	elem.x = j - (list->size_x / 2);
	elem.y = i - (list->size_y / 2);
	elem.z = (ft_atoi(split[j])) * (-1);
	if (ft_strchr(split[j], 'x') != NULL)
		elem.color = ft_atoi_base(ft_strchr(split[j], 'x') + 1, 16);
	else
		elem.color = 0x00FFFFFF;
	return (elem);
}

static	t_read	**read_file(int fd, t_mlx *list)
{
	t_read	**map;
	char	*line;
	int		i;
	int		j;
	char	**split;

	i = 0;
	map = struct_alloc(list->size_y, list->size_x, list);
	while (get_next_line(fd, &line) > 0 && i < list->size_y)
	{
		j = 0;
		split = ft_strsplit(line, ' ');
		while (split[j] != NULL && j < list->size_x)
		{
			map[i][j] = include_var(i, j, split, list);
			j++;
		}
		i++;
	}
	close(fd);
	list->flag1 = 0;
	list->flag2 = 0;
	list->new_z = 0;
	return (map);
}

static	int		is_valid(char *file_name, t_mlx *list)
{
	int		fd;
	char	*line;
	int		size;
	int		curr;

	size = 0;
	curr = 0;
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	if (get_next_line(fd, &line) == 0)
		return (0);
	while (ft_strsplit(line, ' ')[size] != NULL)
		size++;
	list->size_x = size;
	list->size_y = 1;
	while (get_next_line(fd, &line) > 0)
	{
		list->size_y++;
		while (ft_strsplit(line, ' ')[curr] != NULL)
			curr++;
		if (curr != size)
			return (0);
	}
	return (1);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_read	**map;
	t_mlx	*list;

	list = (t_mlx*)malloc(sizeof(t_mlx));
	if (argc != 2)
	{
		ft_putstr("usage: ./fdf path/file_name\n");
		return (-1);
	}
	if (is_valid(argv[1], list) == 0)
	{
		ft_putstr("Invalid map!\n");
		return (-1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	map = read_file(fd, list);
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, SIZE_X, SIZE_Y, argv[1]);
	list->img_ptr = mlx_new_image(list->mlx, SIZE_X, SIZE_Y);
	list->img = mlx_get_data_addr(list->img_ptr,
		&(list->pixel_size), &(list->line_size), &(list->endian));
	draw_map(map, list);
	close(fd);
}
