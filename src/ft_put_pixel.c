/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:03:26 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:24:42 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	ft_percent(int current, int start, int end)
{
	int			position;
	int			length;

	position = current - start;
	length = end - start;
	if (!length)
		return (1.0);
	else
		return ((double)position / (double)length);
}

static int		ft_get_gradient(int start, int end, double percent)
{
	double		gradient;

	gradient = (1 - percent) * start + percent * end;
	return ((int)gradient);
}

static int		ft_get_color(int x, int y, t_point start, t_point end)
{
	int			red;
	int			green;
	int			blue;
	double		percent;

	if (ft_abs(end.x - start.x) > ft_abs(end.y - start.y))
		percent = ft_percent(x, start.x, end.x);
	else
		percent = ft_percent(y, start.y, end.y);
	red = ft_get_gradient((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF, percent);
	green = ft_get_gradient((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF, percent);
	blue = ft_get_gradient(start.color & 0xFF, end.color & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}

static int		ft_get_height(int x, int y, t_point start, t_point end)
{
	double		height;
	double		percent;

	if (ft_abs(end.x - start.x) > ft_abs(end.y - start.y))
		percent = ft_percent(x, start.x, end.x);
	else
		percent = ft_percent(y, start.y, end.y);
	height = ft_get_gradient(start.z, end.z, percent);
	return (height);
}

void			ft_put_pixel(t_point actual, t_point start, t_point end,
																t_conf *conf)
{
	int			z;
	int			pix;

	pix = actual.y * conf->resolution_x + actual.x;
	if (!conf->hidden_face)
		conf->img.img_data[pix] = ft_get_color(actual.x, actual.y, start, end);
	else
	{
		z = ft_get_height(actual.x, actual.y, start, end);
		if (conf->zbuff[pix] < z)
		{
			conf->zbuff[pix] = z;
			conf->img.img_data[pix] = ft_get_color(actual.x, actual.y, start,
										end);
			conf->edge[pix]++;
		}
		conf->triangle[pix]++;
	}
}
