/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_move_ft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:32:09 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:39:30 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			hook_move_shift(int dir, int value, t_conf *conf)
{
	if (dir == 1)
		conf->coef.move_x -= value;
	else if (dir == 2)
		conf->coef.move_x += value;
	else if (dir == 3)
		conf->coef.move_y -= value;
	else if (dir == 4)
		conf->coef.move_y += value;
	ft_init_grid(conf);
	if (conf->opt[1])
		ft_printf("{MAG}Translate grid - x:%d, y:%d.\n{OFF}", conf->coef.move_x,
					conf->coef.move_y);
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->img.img_ptr,
								0, 0);
	hook_print_hud(conf);
}

void			hook_move_zoom(int dir, t_conf *conf)
{
	if (dir == 1)
		conf->coef.zoom++;
	else if (dir == 2)
	{
		if (conf->coef.zoom == -99)
			ft_printf("{RED}Zoom Min reached !\n{OFF}", conf->coef.zoom);
		else
			conf->coef.zoom--;
	}
	ft_init_grid(conf);
	if (conf->opt[1])
		ft_printf("{MAG}Zoom grid:%d.\n{OFF}", conf->coef.zoom);
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->img.img_ptr,
								0, 0);
	hook_print_hud(conf);
}

static void		ft_move_rotate(int axe, int dir, int value, t_conf *conf)
{
	if (axe == 1)
	{
		if (dir == 1)
			conf->coef.rotate_x -= value;
		else if (dir == 2)
			conf->coef.rotate_x += value;
	}
	else if (axe == 2)
	{
		if (dir == 1)
			conf->coef.rotate_y -= value;
		else if (dir == 2)
			conf->coef.rotate_y += value;
	}
	else if (axe == 3)
	{
		if (dir == 1)
			conf->coef.rotate_z -= value;
		else if (dir == 2)
			conf->coef.rotate_z += value;
	}
}

void			hook_move_rotate(int axe, int dir, int value, t_conf *conf)
{
	ft_move_rotate(axe, dir, value, conf);
	ft_init_grid(conf);
	if (conf->opt[1])
		ft_printf("{MAG}Rotate grid - x:%d, y:%d, z:%d.\n{OFF}",
				conf->coef.rotate_x, conf->coef.rotate_y, conf->coef.rotate_z);
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->img.img_ptr,
								0, 0);
	hook_print_hud(conf);
}

void			hook_move_height(int dir, t_conf *conf)
{
	if (dir == 1)
		conf->coef.move_z++;
	else if (dir == 2)
		conf->coef.move_z--;
	ft_init_grid(conf);
	if (conf->opt[1])
		ft_printf("{MAG}Modify height grid:%d.\n{OFF}", conf->coef.move_z);
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->img.img_ptr,
								0, 0);
	hook_print_hud(conf);
}
