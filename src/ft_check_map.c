/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:44:39 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 21:45:56 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_get_line_size(char *line, int ret, t_conf *conf)
{
	if (ret)
	{
		conf->map_size_y++;
		ret = 0;
		while (line[ret] != '\0')
			ret++;
	}
	return (ret);
}

static void	ft_check_value(char *line, int size, t_conf *conf)
{
	int		i;
	int		value;
	int		line_size_x;

	i = 0;
	value = 0;
	line_size_x = 0;
	while (i < size)
	{
		while (line[i] == ' ')
			i++;
		value = ft_atoi(&line[i]);
		if (conf->zmax < value)
			conf->zmax = value;
		else if (conf->zmin > value)
			conf->zmin = value;
		while (line[i] != ' ' && line[i] != '\n' && line[i] != 0)
			i++;
		while (line[i] == ' ')
			i++;
		line_size_x++;
	}
	if (conf->map_size_x < line_size_x)
		conf->map_size_x = line_size_x;
}

static int	ft_check_line(int fd, t_conf *conf)
{
	int		ret;
	int		size;
	char	*line;

	ret = 1;
	size = 0;
	line = NULL;
	while (ret)
	{
		if ((ret = ft_get_next_line(fd, &line)) < 0)
			return (-3);
		size = ft_get_line_size(line, ret, conf);
		ft_check_value(line, size, conf);
		free(line);
		line = NULL;
	}
	return (0);
}

int			ft_check_map(t_conf *conf)
{
	int		fd;

	fd = 0;
	conf->map_size_x = 0;
	conf->map_size_y = 0;
	if ((fd = open(conf->map_path, O_RDONLY)) < 0)
		return (-2);
	if (ft_check_line(fd, conf) < 0)
		return (-3);
	if (close(fd) < 0)
		return (-9);
	return (0);
}
