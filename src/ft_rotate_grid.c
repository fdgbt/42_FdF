/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_grid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:25:12 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:25:57 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_rotate_x(int x, int y, double angle, t_conf *conf)
{
	int		x_old;
	int		y_old;
	double	z_old;

	x_old = conf->grid[x][y].x;
	y_old = conf->grid[x][y].y;
	z_old = conf->grid[x][y].z;
	conf->grid[x][y].x = x_old;
	conf->grid[x][y].y = y_old * cos(angle) + z_old * -sin(angle);
	conf->grid[x][y].z = y_old * sin(angle) + z_old * cos(angle);
}

static void	ft_rotate_y(int x, int y, double angle, t_conf *conf)
{
	int		x_old;
	int		y_old;
	double	z_old;

	x_old = conf->grid[x][y].x;
	y_old = conf->grid[x][y].y;
	z_old = conf->grid[x][y].z;
	conf->grid[x][y].x = x_old * cos(angle) + z_old * sin(angle);
	conf->grid[x][y].y = y_old;
	conf->grid[x][y].z = x_old * -sin(angle) + z_old * cos(angle);
}

static void	ft_rotate_z(int x, int y, double angle, t_conf *conf)
{
	int		x_old;
	int		y_old;
	double	z_old;

	x_old = conf->grid[x][y].x;
	y_old = conf->grid[x][y].y;
	z_old = conf->grid[x][y].z;
	conf->grid[x][y].x = x_old * cos(angle) + y_old * -sin(angle);
	conf->grid[x][y].y = x_old * sin(angle) + y_old * cos(angle);
	conf->grid[x][y].z = z_old;
}

void		ft_rotate_grid(int x, int y, t_conf *conf)
{
	double	rad_x;
	double	rad_y;
	double	rad_z;
	int		middle_x;
	int		middle_y;

	middle_x = 0;
	middle_y = 0;
	if (conf->projection != 2)
	{
		middle_x = conf->resolution_x / 2;
		middle_y = conf->resolution_y / 2;
	}
	rad_x = ft_deg_to_rad((double)conf->coef.rotate_x);
	rad_y = ft_deg_to_rad((double)conf->coef.rotate_y);
	rad_z = ft_deg_to_rad((double)conf->coef.rotate_z);
	conf->grid[x][y].x -= middle_x;
	conf->grid[x][y].y -= middle_y;
	ft_rotate_x(x, y, rad_x, conf);
	ft_rotate_y(x, y, rad_y, conf);
	ft_rotate_z(x, y, rad_z, conf);
	conf->grid[x][y].x += middle_x;
	conf->grid[x][y].y += middle_y;
}
