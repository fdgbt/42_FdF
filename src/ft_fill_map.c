/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:52:08 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 21:53:08 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_init_color(int z, t_conf *conf)
{
	if (z > conf->zmax * 0.6)
		return (D_SNOW);
	else if (z > conf->zmax * 0.2)
		return (D_ROCK);
	else if (z > conf->zmax * 0.1)
		return (D_FOREST);
	else if (z > 0 || (!z && !conf->zmin))
		return (D_GROUND);
	else if (z > conf->zmin * 0.2 && conf->zmin < -2)
		return (D_FOAM);
	else if (z > conf->zmin * 0.6 && conf->zmin < -3)
		return (D_SEA);
	else
		return (D_DEEP);
}

static void	ft_fill_value(char **values, int y, t_conf *conf)
{
	int		x;

	x = 0;
	while (values[x] != 0)
	{
		conf->map[x][y].x = D_GRID_X * x;
		conf->map[x][y].y = D_GRID_Y * y;
		conf->map[x][y].z = ft_atoi(values[x]);
		conf->map[x][y].color = ft_init_color(conf->map[x][y].z, conf);
		x++;
	}
	if (x)
	{
		while (x < conf->map_size_x)
		{
			conf->map[x][y].x = D_GRID_X * x;
			conf->map[x][y].y = D_GRID_Y * y;
			conf->map[x][y].z = 0;
			conf->map[x][y].color = ft_init_color(conf->map[x][y].z, conf);
			x++;
		}
	}
}

static void	ft_clean_input(char *line, char **values)
{
	int		i;

	i = 0;
	while (values[i] != 0)
		free(values[i++]);
	free(values[i]);
	free(values);
	free(line);
}

static int	ft_fill_line(int fd, t_conf *conf)
{
	char	*line;
	char	**values;
	int		ret;
	int		y;

	ret = 1;
	y = 0;
	while (ret)
	{
		line = NULL;
		values = NULL;
		if ((ret = ft_get_next_line(fd, &line)) < 0)
			return (-3);
		if (!(values = ft_strsplit(line, ' ')))
			return (-4);
		ft_fill_value(values, y, conf);
		ft_clean_input(line, values);
		y++;
	}
	return (0);
}

int			ft_fill_map(t_conf *conf)
{
	int		fd;
	int		err;

	fd = 0;
	err = 0;
	if ((fd = open(conf->map_path, O_RDONLY)) < 0)
		return (-2);
	if ((err = ft_fill_line(fd, conf)) < 0)
		return (err);
	if (close(fd) < 0)
		return (-9);
	return (0);
}
