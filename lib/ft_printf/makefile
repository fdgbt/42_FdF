# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 17:34:44 by fdagbert          #+#    #+#              #
#    Updated: 2020/08/06 15:05:48 by fdagbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m

NAME = libftprintf.a

SRC_PATH = src
FUNCTIONS = ft_printf.c			\
			ft_check_flags.c	\
			ft_check_conf.c		\
			ft_set_wild.c		\
			ft_addbuff.c		\
			ft_imtoa_base.c		\
			ft_umtoa_base.c		\
			ft_conv_int.c		\
			ft_fill_int.c		\
			ft_conv_new.c		\
			ft_conv_char.c		\
			ft_conv_utf8.c		\
			ft_conv_string.c	\
			ft_conv_wstr.c		\
			ft_conv_address.c	\
			ft_conv_pct.c		\
			ft_conv_ctrl.c		\
			ft_conv_date.c		\
			ft_format_date.c	\
			ft_conv_fd.c		\
			ft_conv_file.c		\
			ft_conv_crypt.c		\
			ft_text_effects.c
SRC = $(addprefix $(SRC_PATH)/,$(FUNCTIONS))

OBJ_PATH = obj
OBJ_FUNCT = $(FUNCTIONS:.c=.o)
OBJ_SRC = $(addprefix $(OBJ_PATH)/,$(OBJ_FUNCT))

OBJECTS = $(OBJ_SRC)

INC_PATH = include
INC_SRC = $(LIBFT_PATH)/$(INC_PATH)/libft.h					\
			$(LIBFT_PATH)/$(INC_PATH)/ft_get_next_line.h	\
			$(INC_PATH)/ft_printf.h

LIBFT_PATH = ../libft
LIBFT_NAME = libft.a

INCLUDES = $(LIBFT_PATH)/$(INC_PATH) $(INC_PATH)
INC_CC = $(foreach DIR,$(INCLUDES),-I$(DIR))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all, clean, fclean, re, lib

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_PATH)/$(LIBFT_NAME)
	@printf "$(BLUE)Compiling... $(RESET)"
	@cp $(LIBFT_PATH)/$(LIBFT_NAME) $(NAME) 2> /dev/null || true
	@ar -rcs $(NAME) $^
	@ranlib $(NAME)
	@printf "$(GREEN)$(NAME) is ready ! ✓\n$(YELLOW)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC_SRC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@printf "$(BLUE)Compiling... $<$(RESET)"
	@$(CC) -g $(CFLAGS) $(INC_CC) -o $@ -c $<
	@printf "$(BLUE) OK\n$(RESET)"

clean:
	@printf "$(RED)"
	@rm -fv $(OBJECTS)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@printf "$(YELLOW)"

fclean: clean
	@printf "$(RED)"
	@rm -fv $(NAME)
	@printf "$(RESET)"

re: fclean all
