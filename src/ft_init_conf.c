/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_conf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:53:27 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 21:53:56 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_init_mouse(t_conf *conf)
{
	conf->mouse.shift = 0;
	conf->mouse.rotate = 0;
	conf->mouse.xold = 0;
	conf->mouse.yold = 0;
}

static void	ft_init_coef(t_conf *conf)
{
	conf->coef.move_x = 0;
	conf->coef.move_y = 0;
	conf->coef.move_z = 1;
	conf->coef.rotate_x = 0;
	conf->coef.rotate_y = 0;
	conf->coef.rotate_z = 0;
	conf->coef.zoom = 0;
	conf->coef.z_offset = 2;
}

static void	ft_init_img(t_conf *conf)
{
	conf->img.img_ptr = NULL;
	conf->img.img_data = NULL;
	conf->img.bpp = 0;
	conf->img.size_l = 0;
	conf->img.endian = 0;
}

static void	ft_init_ptr(t_conf *conf)
{
	conf->map_path = NULL;
	conf->zbuff = NULL;
	conf->triangle = NULL;
	conf->edge = NULL;
	conf->mlx_ptr = NULL;
	conf->win_ptr = NULL;
	conf->map = NULL;
	conf->grid = NULL;
}

void		ft_init_conf(t_conf *conf)
{
	ft_bzero((void *)conf->opt, D_OPT_MAX);
	ft_bzero((void *)conf->title, D_TITLE_MAX);
	conf->keys[0] = 'h';
	conf->keys[1] = 'v';
	conf->keys[2] = 'z';
	conf->keys[3] = 'r';
	conf->keys[4] = '0';
	conf->resolution_x = 0;
	conf->resolution_y = 0;
	conf->force_res = 0;
	conf->map_size_x = 0;
	conf->map_size_y = 0;
	conf->zmax = 0;
	conf->zmin = 0;
	conf->auto_size = 0;
	conf->projection = 0;
	conf->hidden_face = 0;
	conf->hidden_hud = 0;
	ft_init_mouse(conf);
	ft_init_coef(conf);
	ft_init_img(conf);
	ft_init_ptr(conf);
}
