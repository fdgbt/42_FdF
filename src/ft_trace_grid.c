/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:31:18 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:31:58 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_trace_triangle(int x, int y, t_conf *conf)
{
	if (x + 1 < conf->map_size_x)
		ft_bresenham(conf->grid[x][y], conf->grid[x + 1][y], conf);
	if (y + 1 < conf->map_size_y)
		ft_bresenham(conf->grid[x][y], conf->grid[x][y + 1], conf);
	if (conf->hidden_face)
	{
		if (x + 1 < conf->map_size_x && y + 1 < conf->map_size_y)
			ft_bresenham(conf->grid[x][y + 1], conf->grid[x + 1][y + 1], conf);
		if (x + 1 < conf->map_size_x && y + 1 < conf->map_size_y)
			ft_bresenham(conf->grid[x + 1][y], conf->grid[x + 1][y + 1], conf);
	}
}

void		ft_trace_grid(int x, int y, t_conf *conf)
{
	int		i;
	int		j;

	while (y < conf->map_size_y)
	{
		x = 0;
		while (x < conf->map_size_x)
		{
			if (!conf->grid[x][y].disabled)
				ft_trace_triangle(x, y, conf);
			if (conf->hidden_face && !conf->grid[x][y].disabled)
			{
				ft_fill_grid(conf);
				i = 0;
				j = conf->resolution_x * conf->resolution_y;
				while (i < j)
				{
					conf->triangle[i] = 0;
					i++;
				}
			}
			x++;
		}
		y++;
	}
}
