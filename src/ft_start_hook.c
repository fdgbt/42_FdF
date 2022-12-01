/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:29:19 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:31:04 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_shift_mouse(int x, int y, t_conf *param)
{
	if (param->mouse.shift)
	{
		if (param->mouse.xold < x)
			hook_move_shift(2, 1, param);
		else if (param->mouse.xold > x)
			hook_move_shift(1, 1, param);
		if (param->mouse.yold < y)
			hook_move_shift(4, 1, param);
		else if (param->mouse.yold > y)
			hook_move_shift(3, 1, param);
	}
	if (param->mouse.rotate)
	{
		if (param->mouse.xold < x)
			hook_move_rotate(2, 2, 1, param);
		else if (param->mouse.xold > x)
			hook_move_rotate(2, 1, 1, param);
		if (param->mouse.yold < y)
			hook_move_rotate(1, 1, 1, param);
		else if (param->mouse.yold > y)
			hook_move_rotate(1, 2, 1, param);
	}
	param->mouse.xold = x;
	param->mouse.yold = y;
	return (0);
}

static int	ft_press_button(int button, int x, int y, t_conf *param)
{
	if (param->opt[1])
		ft_printf("{BLU}Mouse button detected: button:%d, x:%d, y:%d\n{OFF}",
					button, x, y);
	if (button == 1)
		param->mouse.rotate++;
	else if (button == 3)
		param->mouse.shift++;
	else if (button == 4)
		hook_move_zoom(1, param);
	else if (button == 5)
		hook_move_zoom(2, param);
	return (0);
}

static int	ft_release_button(int button, int x, int y, t_conf *param)
{
	if (param->opt[1])
		ft_printf("{BLU}Mouse button released - button:%d, x:%d, y:%d\n{OFF}",
					button, x, y);
	if (button == 1)
		param->mouse.rotate = 0;
	else if (button == 3)
		param->mouse.shift = 0;
	return (0);
}

static int	ft_exit_hook(t_conf *param)
{
	return (ft_end(0, param));
}

int			ft_start_hook(t_conf *conf)
{
	if (conf->opt[1])
		ft_printf("{YEL}Initializing Hook...\n{OFF}");
	mlx_hook(conf->win_ptr, KeyPress, KeyPressMask, ft_press_key, conf);
	mlx_hook(conf->win_ptr, ButtonPress, ButtonPressMask, ft_press_button,
				conf);
	mlx_hook(conf->win_ptr, ButtonRelease, ButtonReleaseMask, ft_release_button,
				conf);
	mlx_hook(conf->win_ptr, MotionNotify, PointerMotionMask, ft_shift_mouse,
				conf);
	mlx_hook(conf->win_ptr, DestroyNotify, StructureNotifyMask, ft_exit_hook,
				conf);
	if (conf->opt[1])
		ft_printf("{YEL}Hook ready ! Starting loop...\n{OFF}");
	mlx_loop(conf->mlx_ptr);
	return (0);
}
