/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:51:16 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 21:51:47 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_print_error(char *error)
{
	ft_printf("%@{RED}ERROR\n%@%s{OFF}\n", 1, 2, error);
}

static void	ft_init_error_fdf(int error)
{
	char	error_tab[20][50];

	ft_bzero(error_tab[0], 50);
	ft_strcpy(error_tab[1], "Memory limit (malloc)");
	ft_strcpy(error_tab[2], "Failed to open map file (wrong name)");
	ft_strcpy(error_tab[3], "Failed to read map file (GNL)");
	ft_strcpy(error_tab[4], "Failed to split map file (strsplit)");
	ft_strcpy(error_tab[5], "Failed to set up connection to server (mlx_init)");
	ft_strcpy(error_tab[6], "Failed to create new window (mlx_new_window)");
	ft_strcpy(error_tab[7], "Failed to create new img (mlx_new_image)");
	ft_strcpy(error_tab[8], "Failed to get image infos (mlx_get_data_addr)");
	ft_strcpy(error_tab[9], "Failed to close map file (wrong fd)");
	ft_strcpy(error_tab[10], "Invalid argument (wrong opt)");
	ft_strcpy(error_tab[11], "Invalid argument (too much maps)");
	ft_strcpy(error_tab[12], "Invalid argument (map file missing)");
	ft_strcpy(error_tab[13], "Failed to open man (man file missing)");
	ft_strcpy(error_tab[14], "Failed to close man (wrong fd)");
	ft_strcpy(error_tab[15], "Failed to create map (no data)");
	ft_strcpy(error_tab[16], "RESERVED");
	ft_strcpy(error_tab[17], "RESERVED");
	ft_strcpy(error_tab[18], "RESERVED");
	ft_strcpy(error_tab[19], "RESERVED");
	ft_print_error(error_tab[error]);
}

static void	ft_clean_memory(t_conf *conf)
{
	int		i;

	i = 0;
	if (conf->zbuff)
		free(conf->zbuff);
	if (conf->triangle)
		free(conf->triangle);
	if (conf->edge)
		free(conf->edge);
	if (conf->map)
	{
		i = 0;
		while (i < conf->map_size_x && conf->map[i])
			free(conf->map[i++]);
		free(conf->map);
	}
	if (conf->grid)
	{
		i = 0;
		while (i < conf->map_size_x && conf->grid[i])
			free(conf->grid[i++]);
		free(conf->grid);
	}
}

static void	ft_clean_mlx(t_conf *conf)
{
	if (conf->img.img_ptr)
		mlx_destroy_image(conf->mlx_ptr, conf->img.img_ptr);
	if (conf->win_ptr)
	{
		mlx_clear_window(conf->mlx_ptr, conf->win_ptr);
		mlx_destroy_window(conf->mlx_ptr, conf->win_ptr);
	}
	if (conf->mlx_ptr)
		free(conf->mlx_ptr);
}

int			ft_end(int error, t_conf *conf)
{
	if (error < 0)
		ft_init_error_fdf(-(error));
	if (conf->opt[1])
		ft_printf("{YEL}Stop received. Cleaning memory...\n{OFF}",
					conf->coef.move_x, conf->coef.move_y);
	ft_clean_memory(conf);
	ft_clean_mlx(conf);
	if (conf->opt[1])
		ft_printf("{YEL}Memory cleaned. Exiting now !\n{OFF}",
					conf->coef.move_x, conf->coef.move_y);
	exit(error);
}
