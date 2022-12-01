# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 16:04:21 by bwan-nan          #+#    #+#              #
#    Updated: 2022/12/01 21:05:21 by fdagbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

END=\x1b[0m
RESET=\033[0m
BLACK=\033[0;30m
RED=\033[0;31m
GREEN =\033[32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m

NAME = fdf
DSYM = $(NAME).dSYM

SRC_PATH = src
LIB_PATH = lib
OBJ_PATH = obj
INC_PATH = include

LIBFT = libft.a
LIBPTF = libftprintf.a
LIBMLX = libmlx.a
LIBMLX_LINUX = libmlx_Linux.a

LIBFT_PATH = $(LIB_PATH)/libft
LIBPTF_PATH = $(LIB_PATH)/ft_printf
LIBMLX_PATH = $(LIB_PATH)/minilibx-linux

FDF_FCT = main.c											\
		  ft_init_conf.c									\
		  ft_init_map.c										\
		  ft_check_map.c									\
		  ft_fill_map.c										\
		  ft_init_memory.c									\
		  ft_init_grid.c									\
		  ft_set_grid.c										\
		  ft_projection.c									\
		  ft_rotate_grid.c									\
		  ft_trace_grid.c									\
		  ft_bresenham.c									\
		  ft_put_pixel.c									\
  		  ft_fill_grid.c									\
		  ft_start_hook.c									\
		  ft_press_key.c									\
		  hook_switch_ft.c									\
		  hook_move_ft.c									\
		  ft_end.c											
FDF_SRC = $(addprefix $(SRC_PATH)/,$(FDF_FCT))

FDF_OBJ = $(FDF_FCT:.c=.o)
FDF_OBJ_SRC = $(addprefix $(OBJ_PATH)/,$(FDF_OBJ))

OBJECTS = $(FDF_OBJ_SRC)

HEAD_SRC = $(LIBFT_PATH)/$(INC_PATH)/libft.h				\
		   $(LIBFT_PATH)/$(INC_PATH)/ft_get_next_line.h		\
		   $(LIBPTF_PATH)/$(INC_PATH)/ft_printf.h			\
		   $(LIBMLX_PATH)/mlx.h								\
		   $(INC_PATH)/fdf.h

CC = clang
CFLAGS = -Wall -Wextra -Werror -O3
DFLAGS = -fsanitize=address

LIBPTF_FLAGS = -L$(LIB_PATH)/ft_printf -lftprintf
LBX_FLAGS = -L$(LIB_PATH)/minilibx-linux -lX11 -lXext -lmlx -lm -lbsd
LBX_MAC_FLAGS = -framework OpenGL -framework AppKit

INCLUDES = $(LIBFT_PATH)/$(INC_PATH) $(LIBPTF_PATH)/$(INC_PATH) $(LIBMLX_PATH) \
			$(INC_PATH)
INC_CC = $(foreach DIR,$(INCLUDES),-I$(DIR))

.PHONY: all, clean, fclean, re, lib

all:
	@printf "$(YELLOW)"
	@$(MAKE) $(NAME)
	@printf "$(RESET)"

$(NAME): $(LIBFT_PATH)/$(LIBFT) $(LIBPTF_PATH)/$(LIBPTF) $(OBJECTS)
	@printf "$(PURPLE)Compiling... $(RESET)"
	@$(CC) -o $(NAME) $(OBJECTS) $(INC_CC) $(LIBPTF_FLAGS) $(LBX_FLAGS)
	@printf "$(GREEN)$(NAME) is ready ! ✓\n$(YELLOW)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEAD_SRC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@printf "$(PURPLE)Compiling... $<$(RESET)"
	@$(CC) -g $(CFLAGS) $(INC_CC) -o $@ -c $<
	@printf "$(PURPLE) OK\n$(RESET)"

$(LIBFT_PATH)/$(LIBFT): lib

lib:
	@printf "$(YELLOW)"
	@$(MAKE) -C $(LIBMLX_PATH)
	@$(MAKE) -C $(LIBFT_PATH)
	@$(MAKE) -C $(LIBPTF_PATH)

clean:
	@printf "$(YELLOW)"
	@$(MAKE) -C $(LIBMLX_PATH) clean
	@printf "$(YELLOW)"
	@$(MAKE) -C $(LIBFT_PATH) clean
	@printf "$(YELLOW)"
	@$(MAKE) -C $(LIBPTF_PATH) clean
	@printf "$(RED)"
	@rm -fv $(OBJECTS)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@rm -fv $(DSYM)
	@printf "$(RESET)"

fclean: clean
	@printf "$(RED)"
	@rm -fv $(LIBFT_PATH)/$(LIBFT)
	@rm -fv $(LIBPTF_PATH)/$(LIBPTF)
	@rm -fv $(NAME)
	@printf "$(RESET)"

re: fclean all
