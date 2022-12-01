/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:47:54 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 21:51:07 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	ft_gradient(int start, int end, double percent)
{
	return ((1 - percent) * start + percent * end);
}

static double	ft_percent(int actual, int start, int end)
{
	int			position;
	int			length;
	double		percent;

	position = actual - start;
	length = end - start;
	if (!length)
		percent = 1.0;
	else
		percent = (double)position / (double)length;
	return (percent);
}

static int		ft_fill_color(t_point actual, t_point start, t_point end,
																t_conf *conf)
{
	int			pix;
	int			red;
	int			green;
	int			blue;
	double		percent;

	pix = actual.y * conf->resolution_x;
	percent = ft_percent(actual.x, start.x, end.x);
	red = ft_gradient((conf->img.img_data[pix + start.x] >> 16) & 0xFF,
				(conf->img.img_data[pix + end.x] >> 16) & 0xFF, percent);
	green = ft_gradient((conf->img.img_data[pix + start.x] >> 8) & 0xFF,
				(conf->img.img_data[pix + end.x] >> 8) & 0xFF, percent);
	blue = ft_gradient(conf->img.img_data[pix + start.x] & 0xFF,
				conf->img.img_data[pix + end.x] & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

static void		ft_fill_line(t_point actual, t_point start, t_point end,
																t_conf *conf)
{
	int			pix;
	double		percent;

	pix = actual.y * conf->resolution_x;
	start.z = conf->zbuff[pix + start.x];
	end.z = conf->zbuff[pix + end.x];
	actual.x = start.x + 1;
	while (actual.x < end.x)
	{
		pix = actual.y * conf->resolution_x + actual.x;
		percent = ft_percent(actual.x, start.x, end.x);
		actual.z = ft_gradient(start.z, end.z, percent);
		if (conf->projection == 2)
			actual.z = -actual.z;
		if (actual.z > conf->zbuff[pix])
		{
			conf->edge[pix] = 0;
			conf->zbuff[pix] = actual.z;
			conf->img.img_data[pix] = ft_fill_color(actual, start, end, conf);
		}
		actual.x++;
	}
}

void			ft_fill_grid(t_conf *conf)
{
	int			pix;
	t_point		start;
	t_point		end;
	t_point		actual;

	actual.y = 0;
	while (actual.y < conf->resolution_y)
	{
		start.x = 0;
		end.x = conf->resolution_x - 1;
		pix = actual.y * conf->resolution_x;
		while (start.x < end.x && start.x < conf->resolution_x - 1
				&& !conf->triangle[pix + start.x])
			start.x++;
		while (start.x < end.x && start.x < conf->resolution_x - 1
				&& conf->triangle[pix + start.x + 1])
			start.x++;
		while (end.x > start.x && end.x > 0 && !conf->triangle[pix + end.x])
			end.x--;
		while (end.x > start.x && end.x > 0 && conf->triangle[pix + end.x - 1])
			end.x--;
		if (start.x < end.x)
			ft_fill_line(actual, start, end, conf);
		actual.y++;
	}
}
