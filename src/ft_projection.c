/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:02:17 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:03:19 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_grid_isometric(int x, int y, t_conf *conf)
{
	int		x_old;
	int		y_old;
	int		z_old;

	ft_rotate_grid(x, y, conf);
	x_old = conf->grid[x][y].x;
	y_old = conf->grid[x][y].y;
	z_old = conf->grid[x][y].z;
	conf->grid[x][y].x = (x_old - y_old) * cos(0.523599);
	conf->grid[x][y].y = (x_old + y_old) * sin(0.523599) - z_old;
}

static void	ft_grid_cabinet(int x, int y, t_conf *conf)
{
	int		x_old;
	int		y_old;
	int		z_old;

	ft_rotate_grid(x, y, conf);
	x_old = conf->grid[x][y].x;
	y_old = conf->grid[x][y].y;
	z_old = conf->grid[x][y].z;
	conf->grid[x][y].x = (x_old - y_old) - z_old * cos(0.523599);
	conf->grid[x][y].y = y_old - z_old * sin(0.523599);
}

static void	ft_grid_perspective(int x, int y, t_conf *conf)
{
	if (!(conf->map_size_x % 2))
		conf->grid[x][y].x = conf->grid[x][y].x - (conf->map_size_x / 2)
								* D_GRID_X + D_GRID_X / 2;
	else
		conf->grid[x][y].x = conf->grid[x][y].x - (conf->map_size_x / 2)
								* D_GRID_X;
	if (!(conf->map_size_y % 2))
		conf->grid[x][y].y = conf->grid[x][y].y - (conf->map_size_y / 2)
								* D_GRID_Y + D_GRID_Y / 2;
	else
		conf->grid[x][y].y = conf->grid[x][y].y - (conf->map_size_y / 2)
								* D_GRID_Y;
	ft_rotate_grid(x, y, conf);
	conf->grid[x][y].z = -((conf->grid[x][y].z - conf->zmin)
							/ (conf->zmax - conf->zmin) - 0.5) * 0.1;
	conf->grid[x][y].z++;
	if (conf->map_size_x > 20 && conf->map_size_y > 20)
		conf->grid[x][y].z++;
	conf->grid[x][y].x = conf->grid[x][y].x / conf->grid[x][y].z;
	conf->grid[x][y].y = conf->grid[x][y].y / conf->grid[x][y].z;
	if (conf->grid[x][y].z < 0.3)
		conf->grid[x][y].disabled = 1;
}

void		ft_projection(int x, int y, t_conf *conf)
{
	if (conf->projection == 0)
		ft_grid_isometric(x, y, conf);
	else if (conf->projection == 1)
		ft_grid_cabinet(x, y, conf);
	else if (conf->projection == 2)
		ft_grid_perspective(x, y, conf);
}
