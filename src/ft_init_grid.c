/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:54:15 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 21:57:23 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_create_grid(t_conf *conf)
{
	int		x;

	x = 0;
	if (!(conf->grid = (t_point **)malloc(sizeof(*conf->grid)
			* conf->map_size_x)))
		return (-1);
	while (x < conf->map_size_x)
	{
		if (!(conf->grid[x] = (t_point *)malloc(sizeof(**conf->grid)
				* conf->map_size_y)))
			return (-1);
		ft_bzero((void *)conf->grid[x], sizeof(**conf->grid)
			* conf->map_size_y);
		x++;
	}
	return (0);
}

static int	ft_check_border(t_conf *conf)
{
	if (conf->grid[0][0].x < 0 || conf->grid[0][0].x >= conf->resolution_x ||
			conf->grid[0][0].y < 0 || conf->grid[0][0].y >= conf->resolution_y)
		conf->coef.zoom--;
	else if (conf->grid[0][conf->map_size_y - 1].x < 0
			|| conf->grid[0][conf->map_size_y - 1].x >= conf->resolution_x
			|| conf->grid[0][conf->map_size_y - 1].y < 0
			|| conf->grid[0][conf->map_size_y - 1].y >= conf->resolution_y)
		conf->coef.zoom--;
	else if (conf->grid[conf->map_size_x - 1][conf->map_size_y - 1].x < 0
			|| conf->grid[conf->map_size_x - 1][conf->map_size_y - 1].x
				>= conf->resolution_x
			|| conf->grid[conf->map_size_x - 1][conf->map_size_y - 1].y < 0
			|| conf->grid[conf->map_size_x - 1][conf->map_size_y - 1].y
				>= conf->resolution_y)
		conf->coef.zoom--;
	else if (conf->grid[conf->map_size_x - 1][0].x < 0
			|| conf->grid[conf->map_size_x - 1][0].x >= conf->resolution_x
			|| conf->grid[conf->map_size_x - 1][0].y < 0
			|| conf->grid[conf->map_size_x - 1][0].y >= conf->resolution_y)
		conf->coef.zoom--;
	else
		return (0);
	return (1);
}

static int	ft_auto_zoom(t_conf *conf)
{
	int ret;

	ret = ft_check_border(conf);
	if (conf->opt[1])
		ft_printf("{MAG}Automated Zoom: %d\n{OFF}", conf->coef.zoom);
	ft_set_grid(conf);
	return (ret);
}

static void	ft_retrace_edge(t_conf *conf)
{
	int		x;
	int		xmax;

	x = 0;
	xmax = conf->resolution_x * conf->resolution_y;
	while (x < xmax)
	{
		if (conf->edge[x] != 0)
		{
			conf->img.img_data[x] = 0x0;
			conf->edge[x] = 0;
		}
		x++;
	}
}

int			ft_init_grid(t_conf *conf)
{
	if (conf->opt[1])
		ft_printf("{YEL}Initializing grid...\n{OFF}");
	if (!conf->grid)
	{
		if (!conf->opt[2])
			conf->auto_size = 1;
		if (ft_create_grid(conf) < 0)
			return (-1);
	}
	ft_set_grid(conf);
	while (conf->auto_size)
		conf->auto_size = ft_auto_zoom(conf);
	ft_trace_grid(0, 0, conf);
	if (conf->hidden_face)
		ft_retrace_edge(conf);
	if (conf->opt[1])
		ft_printf("{YEL}Grid ready !\n{OFF}");
	return (0);
}
