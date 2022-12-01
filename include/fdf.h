/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 22:44:42 by fdagbert          #+#    #+#             */
/*   Updated: 2020/11/30 22:44:44 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define D_OPT_MAX 5
# define D_TITLE_MAX 50
# define D_GRID_X 32
# define D_GRID_Y 32
# define D_PI 3.14159265358979323846
# define D_MAN_PATH "./src/man/fdf.txt"
# define D_SNOW 0xFFFFFF
# define D_ROCK 0x582900
# define D_FOREST 0x006400
# define D_GROUND 0x008000
# define D_FOAM 0x00AAC0
# define D_SEA 0x0000C0
# define D_DEEP 0x000050

# include <math.h>
# include "ft_printf.h"
# include "mlx.h"
# include "X11/Xlib.h"

typedef struct		s_point
{
	int				x;
	int				y;
	double			z;
	int				color;
	int				disabled;
}					t_point;

typedef struct		s_img
{
	void			*img_ptr;
	int				*img_data;
	int				bpp;
	int				size_l;
	int				endian;
}					t_img;

typedef struct		s_coef
{
	int				move_x;
	int				move_y;
	int				move_z;
	int				rotate_x;
	int				rotate_y;
	int				rotate_z;
	int				zoom;
	int				z_offset;
}					t_coef;

typedef struct		s_mouse
{
	int				shift;
	int				rotate;
	int				xold;
	int				yold;
}					t_mouse;

typedef struct		s_bresenham
{
	int				x;
	int				y;
	int				dx;
	int				dy;
	int				xincr;
	int				yincr;
	int				err;
	int				i;
}					t_bresenham;

typedef struct		s_conf
{
	char			title[D_TITLE_MAX];
	char			keys[D_OPT_MAX];
	int				opt[D_OPT_MAX];
	int				resolution_x;
	int				resolution_y;
	int				force_res;
	int				map_size_x;
	int				map_size_y;
	int				zmax;
	int				zmin;
	int				auto_size;
	int				projection;
	int				hidden_face;
	int				hidden_hud;
	int				*zbuff;
	int				*triangle;
	int				*edge;
	char			*map_path;
	void			*mlx_ptr;
	void			*win_ptr;
	t_point			**map;
	t_point			**grid;
	t_img			img;
	t_coef			coef;
	t_mouse			mouse;
}					t_conf;

int					ft_init_map(t_conf *conf);
int					ft_check_map(t_conf *conf);
int					ft_fill_map(t_conf *conf);
int					ft_init_memory(t_conf *conf);
int					ft_init_grid(t_conf *conf);
int					ft_start_hook(t_conf *conf);
int					ft_press_key(int key, t_conf *param);
int					ft_end(int error, t_conf *conf);
void				ft_init_conf(t_conf *conf);
void				ft_set_grid(t_conf *conf);
void				ft_projection(int x, int y, t_conf *conf);
void				ft_rotate_grid(int x, int y, t_conf *conf);
void				ft_trace_grid(int x, int y, t_conf *conf);
void				ft_bresenham(t_point start, t_point end, t_conf *conf);
void				ft_put_pixel(t_point actual, t_point start, t_point end,
																t_conf *conf);
void				ft_fill_grid(t_conf *conf);
void				hook_move_shift(int dir, int value, t_conf *conf);
void				hook_move_zoom(int dir, t_conf *conf);
void				hook_move_rotate(int axe, int dir, int value, t_conf *conf);
void				hook_move_height(int dir, t_conf *conf);
void				hook_switch_proj(t_conf *conf);
void				hook_switch_face(t_conf *conf);
int					hook_switch_clean(t_conf *conf);
void				hook_switch_hud(t_conf *conf);
void				hook_print_hud(t_conf *conf);

#endif
