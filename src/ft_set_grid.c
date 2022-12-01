/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:26:19 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:29:02 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_reset_grid(t_conf *conf)
{
	int		x;
	int		xmax;

	x = 0;
	if (conf->grid)
	{
		while (x < conf->map_size_x && conf->grid[x])
		{
			ft_bzero((void *)conf->grid[x],
						sizeof(**conf->grid) * conf->map_size_y);
			x++;
		}
	}
	if (conf->hidden_face)
	{
		x = 0;
		xmax = conf->resolution_x * conf->resolution_y;
		while (x < xmax)
			conf->zbuff[x++] = INT32_MIN;
	}
	if (conf->img.img_data)
		ft_bzero((void *)conf->img.img_data,
					4 * conf->resolution_x * conf->resolution_y);
}

static void	ft_set_zoom(int x, int y, t_conf *conf)
{
	if (conf->coef.zoom != 0)
	{
		if (conf->coef.zoom <= -10)
		{
			conf->grid[x][y].x *= (0.1 + 0.001 * conf->coef.zoom);
			conf->grid[x][y].y *= (0.1 + 0.001 * conf->coef.zoom);
			conf->grid[x][y].z *= (0.1 + 0.001 * conf->coef.zoom);
		}
		else
		{
			conf->grid[x][y].x *= (1 + 0.1 * conf->coef.zoom);
			conf->grid[x][y].y *= (1 + 0.1 * conf->coef.zoom);
			conf->grid[x][y].z *= (1 + 0.1 * conf->coef.zoom);
		}
	}
}

static void	ft_generate_grid(t_conf *conf)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < conf->map_size_y)
	{
		x = 0;
		while (x < conf->map_size_x)
		{
			conf->grid[x][y].x = conf->map[x][y].x;
			conf->grid[x][y].y = conf->map[x][y].y;
			conf->grid[x][y].z = conf->map[x][y].z;
			conf->grid[x][y].color = conf->map[x][y].color;
			conf->grid[x][y].disabled = 0;
			if (conf->grid[x][y].z != 0 && conf->coef.move_z != 1)
				conf->grid[x][y].z *= conf->coef.move_z;
			ft_projection(x, y, conf);
			ft_set_zoom(x, y, conf);
			x++;
		}
		y++;
	}
}

static void	ft_center_grid(t_conf *conf)
{
	int		offset_x;
	int		offset_y;
	int		x;
	int		y;

	offset_x = conf->resolution_x / 2
				- conf->grid[conf->map_size_x / 2][conf->map_size_y / 2].x;
	offset_y = conf->resolution_y / 2
				- conf->grid[conf->map_size_x / 2][conf->map_size_y / 2].y;
	y = 0;
	while (y < conf->map_size_y)
	{
		x = 0;
		while (x < conf->map_size_x)
		{
			conf->grid[x][y].x += offset_x;
			conf->grid[x][y].y += offset_y;
			conf->grid[x][y].x += conf->coef.move_x;
			conf->grid[x][y].y += conf->coef.move_y;
			x++;
		}
		y++;
	}
}

void		ft_set_grid(t_conf *conf)
{
	ft_reset_grid(conf);
	ft_generate_grid(conf);
	ft_center_grid(conf);
}
