/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_switch_ft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:39:41 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:41:58 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		hook_print_hud(t_conf *conf)
{
	if (!conf->hidden_hud)
	{
		mlx_string_put(conf->mlx_ptr, conf->win_ptr, 10, 20, 0xFFFFFF,
			"Hide HUD | H");
		mlx_string_put(conf->mlx_ptr, conf->win_ptr, 10, 40, 0xFFFFFF,
			"Reset    | DEL");
		mlx_string_put(conf->mlx_ptr, conf->win_ptr, 10, 60, 0xFFFFFF,
			"Quit     | ESC");
		mlx_string_put(conf->mlx_ptr, conf->win_ptr, conf->resolution_x - 180,
			20, 0xFFFFFF, "Hidden Face | SPACE");
		mlx_string_put(conf->mlx_ptr, conf->win_ptr, conf->resolution_x - 180,
			40, 0xFFFFFF, "Projection  | CTRL LEFT");
		mlx_string_put(conf->mlx_ptr, conf->win_ptr, 10,
			conf->resolution_y - 40, 0xFFFFFF,
			"Translate | X: RIGHT / LEFT - Y: UP / DOWN");
		mlx_string_put(conf->mlx_ptr, conf->win_ptr, 10,
			conf->resolution_y - 20, 0xFFFFFF,
			"Rotate    | X: Z / S - Y: Q / D - Z: A / E");
		mlx_string_put(conf->mlx_ptr, conf->win_ptr, conf->resolution_x - 180,
			conf->resolution_y - 40, 0xFFFFFF, "Height | START / END");
		mlx_string_put(conf->mlx_ptr, conf->win_ptr, conf->resolution_x - 180,
			conf->resolution_y - 20, 0xFFFFFF, "Zoom   | PAGE UP / PAGE DOWN");
	}
}

void		hook_switch_proj(t_conf *conf)
{
	conf->projection++;
	if (conf->projection == 3)
		conf->projection = 0;
	ft_init_grid(conf);
	if (conf->opt[1])
		ft_printf("{MAG}Projection switched:%d.\n{OFF}", conf->projection);
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->img.img_ptr,
								0, 0);
	hook_print_hud(conf);
}

void		hook_switch_face(t_conf *conf)
{
	conf->hidden_face = !conf->hidden_face;
	ft_init_grid(conf);
	if (conf->opt[1] && conf->hidden_face)
		ft_printf("{MAG}Hidden face enabled.{OFF}\n");
	else if (conf->opt[1])
		ft_printf("{MAG}Hidden face disabled.\n{OFF}");
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->img.img_ptr,
								0, 0);
	hook_print_hud(conf);
}

void		hook_switch_hud(t_conf *conf)
{
	conf->hidden_hud = !conf->hidden_hud;
	if (conf->opt[1] && conf->hidden_hud)
		ft_printf("{MAG}HUD hidden.{OFF}\n");
	else if (conf->opt[1])
		ft_printf("{MAG}HUD displayed.\n{OFF}");
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->img.img_ptr,
								0, 0);
	hook_print_hud(conf);
}

int			hook_switch_clean(t_conf *conf)
{
	conf->auto_size = 1;
	conf->hidden_face = 0;
	conf->hidden_hud = 0;
	conf->coef.move_x = 0;
	conf->coef.move_y = 0;
	conf->coef.move_z = 1;
	conf->coef.rotate_x = 0;
	conf->coef.rotate_y = 0;
	conf->coef.rotate_z = 0;
	conf->coef.zoom = 0;
	conf->mouse.shift = 0;
	conf->mouse.rotate = 0;
	conf->mouse.xold = 0;
	conf->mouse.yold = 0;
	ft_init_grid(conf);
	if (conf->opt[1])
		ft_printf("{MAG}Settings reseted.\n{OFF}");
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->img.img_ptr,
								0, 0);
	hook_print_hud(conf);
	return (0);
}
