/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:41:17 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 21:46:37 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		ft_init_bresenham(t_bresenham *bresen, t_point start,
																t_point end)
{
	bresen->x = start.x;
	bresen->y = start.y;
	bresen->dx = ft_abs(end.x - start.x);
	bresen->dy = ft_abs(end.y - start.y);
	if (start.x < end.x)
		bresen->xincr = 1;
	else
		bresen->xincr = -1;
	if (start.y < end.y)
		bresen->yincr = 1;
	else
		bresen->yincr = -1;
	bresen->err = 0;
	bresen->i = 0;
}

static void		ft_go_horizon(t_bresenham *bresen, t_point start, t_point end,
																t_conf *conf)
{
	t_point		actual;

	bresen->err = bresen->dx / 2;
	while (bresen->i < bresen->dx)
	{
		bresen->x += bresen->xincr;
		bresen->err += bresen->dy;
		if (bresen->err > bresen->dx)
		{
			bresen->err -= bresen->dx;
			bresen->y += bresen->yincr;
		}
		actual.x = bresen->x;
		actual.y = bresen->y;
		if (bresen->x >= 0 && bresen->x < conf->resolution_x && bresen->y >= 0
				&& bresen->y < conf->resolution_y)
			ft_put_pixel(actual, start, end, conf);
		bresen->i++;
	}
}

static void		ft_go_vertical(t_bresenham *bresen, t_point start, t_point end,
																t_conf *conf)
{
	t_point		actual;

	bresen->err = bresen->dy / 2;
	while (bresen->i < bresen->dy)
	{
		bresen->y += bresen->yincr;
		bresen->err += bresen->dx;
		if (bresen->err > bresen->dy)
		{
			bresen->err -= bresen->dy;
			bresen->x += bresen->xincr;
		}
		actual.x = bresen->x;
		actual.y = bresen->y;
		if (bresen->x >= 0 && bresen->x < conf->resolution_x && bresen->y >= 0
				&& bresen->y < conf->resolution_y)
			ft_put_pixel(actual, start, end, conf);
		bresen->i++;
	}
}

static void		ft_trace_bresenham(t_bresenham *bresen, t_point start,
													t_point end, t_conf *conf)
{
	if (bresen->dx > bresen->dy)
		ft_go_horizon(bresen, start, end, conf);
	else
		ft_go_vertical(bresen, start, end, conf);
	if (start.x >= 0 && start.x < conf->resolution_x && start.y >= 0
			&& start.y < conf->resolution_y)
		ft_put_pixel(start, start, end, conf);
	if (end.x >= 0 && end.x < conf->resolution_x && end.y >= 0
			&& end.y < conf->resolution_y)
		ft_put_pixel(end, start, end, conf);
}

void			ft_bresenham(t_point start, t_point end, t_conf *conf)
{
	t_bresenham	bresen;

	ft_init_bresenham(&bresen, start, end);
	ft_trace_bresenham(&bresen, start, end, conf);
}
