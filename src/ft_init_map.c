/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:57:36 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:00:30 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_create_map(t_conf *conf)
{
	int		x;

	x = 0;
	if (!(conf->map = (t_point **)malloc(sizeof(*conf->map)
						* conf->map_size_x)))
		return (-1);
	while (x < conf->map_size_x)
	{
		if (!(conf->map[x] = (t_point *)malloc(sizeof(**conf->map)
						* conf->map_size_y)))
			return (-1);
		ft_bzero((void *)conf->map[x], sizeof(**conf->map) * conf->map_size_y);
		x++;
	}
	return (0);
}

static void	ft_print_map(int x, int y, t_conf *conf)
{
	while (y < conf->map_size_y)
	{
		x = 0;
		ft_printf("{WHI}map[%2d]: {OFF}", y);
		while (x < conf->map_size_x)
		{
			if (conf->map[x][y].z)
				ft_printf("{BLU}%3d {OFF}", (int)conf->map[x][y].z);
			else
				ft_printf("{WHI}%3d {OFF}", (int)conf->map[x][y].z);
			x++;
		}
		y++;
		ft_printf("\n{OFF}");
	}
	ft_printf("{MAG}Map datas: size_x: %d, size_y: %d, ",
				conf->map_size_x, conf->map_size_y);
	ft_printf("zmax: %d, zmin: %d\n{OFF}", conf->zmax, conf->zmin);
}

static void	ft_init_resolution(t_conf *conf)
{
	conf->resolution_x = 720;
	conf->resolution_y = 480;
	if (conf->force_res == 2 || conf->force_res > 5 || (!conf->force_res
				&& conf->map_size_x < 20 && conf->map_size_y < 20))
	{
		conf->resolution_x = 800;
		conf->resolution_y = 600;
	}
	else if (conf->force_res == 3 || (!conf->force_res && conf->map_size_x < 50
				&& conf->map_size_y < 50))
	{
		conf->resolution_x = 1280;
		conf->resolution_y = 720;
	}
	else if (conf->force_res == 4 || !conf->force_res)
	{
		conf->resolution_x = 1920;
		conf->resolution_y = 1080;
	}
	else if (conf->force_res == 5)
	{
		conf->resolution_x = 3840;
		conf->resolution_y = 2160;
	}
}

static void	ft_init_title(t_conf *conf)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen("Fil de Fer - ");
	ft_strcpy(conf->title, "Fil de Fer - ");
	while (conf->map_path[i])
		i++;
	i--;
	while (i >= 0 && conf->map_path[i] != '/')
		i--;
	if (i)
		i++;
	while (conf->map_path[i] && j < D_TITLE_MAX)
	{
		conf->title[j] = conf->map_path[i];
		i++;
		j++;
	}
	conf->title[j] = '\0';
}

int			ft_init_map(t_conf *conf)
{
	int		err;

	if (conf->opt[1])
		ft_printf("{YEL}Initializing map...\n{OFF}");
	if ((err = ft_check_map(conf)) < 0)
		return (ft_end(err, conf));
	if ((err = ft_create_map(conf)) < 0)
		return (ft_end(err, conf));
	if ((err = ft_fill_map(conf)) < 0)
		return (ft_end(err, conf));
	if (conf->opt[1])
		ft_print_map(0, 0, conf);
	if (!conf->map_size_x)
		return (-15);
	ft_init_resolution(conf);
	ft_init_title(conf);
	if ((err = ft_init_memory(conf)) < 0)
		return (ft_end(err, conf));
	if (conf->opt[1])
		ft_printf("{YEL}Map ready !\n{OFF}");
	return (0);
}
