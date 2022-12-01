/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_press_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:01:28 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:01:53 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_press_key2(int key, t_conf *param)
{
	if (key == 65360)
		hook_move_zoom(1, param);
	else if (key == 65361)
		hook_move_shift(1, 10, param);
	else if (key == 65362)
		hook_move_shift(3, 10, param);
	else if (key == 65363)
		hook_move_shift(2, 10, param);
	else if (key == 65364)
		hook_move_shift(4, 10, param);
	else if (key == 65365)
		hook_move_height(1, param);
	else if (key == 65366)
		hook_move_height(2, param);
	else if (key == 65367)
		hook_move_zoom(2, param);
	else if (key == 65507)
		hook_switch_proj(param);
	else if (key == 65535)
		hook_switch_clean(param);
}

int			ft_press_key(int key, t_conf *param)
{
	if (param->opt[1])
		ft_printf("{BLU}Key detected:%d.\n{OFF}", key);
	if (key == 32)
		hook_switch_face(param);
	else if (key == 97)
		hook_move_rotate(3, 1, 5, param);
	else if (key == 100)
		hook_move_rotate(2, 2, 5, param);
	else if (key == 101)
		hook_move_rotate(3, 2, 5, param);
	else if (key == 104)
		hook_switch_hud(param);
	else if (key == 113)
		hook_move_rotate(2, 1, 5, param);
	else if (key == 115)
		hook_move_rotate(1, 1, 5, param);
	else if (key == 122)
		hook_move_rotate(1, 2, 5, param);
	else if (key == 65307)
		ft_end(0, param);
	else
		ft_press_key2(key, param);
	return (0);
}
