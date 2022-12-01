/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:00:48 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:01:14 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_init_zbuffer(t_conf *conf)
{
	int		x;
	int		xmax;

	x = 0;
	xmax = conf->resolution_x * conf->resolution_y;
	if (!(conf->zbuff = (int *)malloc(sizeof(*conf->zbuff) * xmax)))
		return (-1);
	while (x < xmax)
	{
		conf->zbuff[x] = INT32_MIN;
		x++;
	}
	return (0);
}

static int	ft_init_triangle(t_conf *conf)
{
	int		xmax;

	xmax = conf->resolution_x * conf->resolution_y;
	if (!(conf->triangle = (int *)malloc(sizeof(*conf->triangle) * xmax)))
		return (-1);
	ft_bzero((void *)conf->triangle, sizeof(*conf->triangle) * xmax);
	return (0);
}

static int	ft_init_edge(t_conf *conf)
{
	int		xmax;

	xmax = conf->resolution_x * conf->resolution_y;
	if (!(conf->edge = (int *)malloc(sizeof(*conf->edge) * xmax)))
		return (-1);
	ft_bzero((void *)conf->edge, sizeof(*conf->edge) * xmax);
	return (0);
}

int			ft_init_memory(t_conf *conf)
{
	int		err;

	err = 0;
	if ((err = ft_init_zbuffer(conf)) < 0)
		return (ft_end(err, conf));
	if ((err = ft_init_triangle(conf)) < 0)
		return (ft_end(err, conf));
	if ((err = ft_init_edge(conf)) < 0)
		return (ft_end(err, conf));
	return (0);
}
