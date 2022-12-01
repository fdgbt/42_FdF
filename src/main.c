/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 00:17:54 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:44:09 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_print_man(void)
{
	int		fd;

	fd = 0;
	if ((fd = open(D_MAN_PATH, O_RDONLY)) < 0)
		return (-13);
	ft_printf("{GRE}%~{OFF}\n", fd);
	if (close(fd) < 0)
		return (-14);
	return (0);
}

static int	ft_check_options(int i, int j, char *argv, t_conf *conf)
{
	while (conf->keys[i])
	{
		if (argv[j] && argv[j] == conf->keys[i])
		{
			if (!conf->opt[i])
				conf->opt[i] = 1;
			else
				return (-10);
			if (i == 3)
			{
				j++;
				if (ft_isdigit(argv[j]))
					conf->force_res = ft_atoi(&argv[j]);
				else
					return (-10);
			}
			if (!argv[++j])
				return (0);
			else
				i = -1;
		}
		i++;
	}
	return (-10);
}

static int	ft_check_args(int err, int i, char **argv, t_conf *conf)
{
	while (i < D_OPT_MAX)
		conf->opt[i++] = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			if (!argv[i][1])
				return (-10);
			if ((err = ft_check_options(0, 1, argv[i], conf)) < 0)
				return (err);
		}
		else if (!conf->map_path)
			conf->map_path = argv[i];
		else
			return (-11);
		i++;
	}
	if (!conf->map_path && !conf->opt[0])
		return (-12);
	return (0);
}

static int	ft_init_window(t_conf *conf)
{
	int		err;

	err = 0;
	if (!(conf->mlx_ptr = mlx_init()))
		return (-5);
	if (!(conf->win_ptr = mlx_new_window(conf->mlx_ptr, conf->resolution_x,
			conf->resolution_y, conf->title)))
		return (-6);
	if (!(conf->img.img_ptr = mlx_new_image(conf->mlx_ptr, conf->resolution_x,
			conf->resolution_y)))
		return (-7);
	if (!(conf->img.img_data = (int *)mlx_get_data_addr(conf->img.img_ptr,
			&conf->img.bpp, &conf->img.size_l, &conf->img.endian)))
		return (-8);
	if ((err = ft_init_grid(conf)) < 0)
		return (err);
	mlx_put_image_to_window(conf->mlx_ptr, conf->win_ptr, conf->img.img_ptr,
							0, 0);
	hook_print_hud(conf);
	return (0);
}

int			main(int argc, char **argv)
{
	int		err;
	t_conf	conf;

	err = 0;
	ft_init_conf(&conf);
	if (argc < 2)
		ft_printf("{GRE}usage: ./fdf test_maps/42.fdf\nhelp : ./fdf -h\n{OFF}");
	else
	{
		if ((err = ft_check_args(0, 0, argv, &conf)) < 0)
			return (ft_end(err, &conf));
		if (conf.opt[0])
			ft_print_man();
		else
		{
			if ((err = ft_init_map(&conf)) < 0)
				return (ft_end(err, &conf));
			if ((err = ft_init_window(&conf)) < 0)
				return (ft_end(err, &conf));
			if ((err = ft_start_hook(&conf)) < 0)
				return (ft_end(err, &conf));
		}
	}
	return (ft_end(err, &conf));
}
