# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 14:51:08 by avan-bre          #+#    #+#              #
#    Updated: 2022/03/30 12:46:22 by avan-bre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################                                                            
#                                 EXECUTBLES                                   #                                                            
################################################################################ 

OS		=	$(shell uname -s)
NAME	=	cub3D
LIBFT	=	libft/libft.a

################################################################################                                                            
#                             COMMANDS AND FLAGS                               #                                                            
################################################################################ 

RM		=	@rm -rf

ifeq ($(OS), Linux)
	CC		=	@clang
else
	CC		=	@gcc
endif

ifeq ($(OS), Linux)
	CL_MLX	=	@make clean -s -C mlx
else
	CL_MLX	=
endif

ifeq ($(OS), Linux)
	MLX		=	libmlx_Linux.a
else
	MLX		=
endif

IFLAGS	=	-I. -Ilibft -Imlx
CFLAGS	=	-Wall -Werror -Wextra $(IFLAGS) $(SFLAGS)
SFLAGS	=	-fsanitize=address -g3
LFLAGS	=	-Llibft -lft

ifeq ($(OS), Linux)
	MFLAGS	:=	-L. -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm
else
	MFLAGS	:= -lmlx -framework OpenGL -framework AppKit
endif

################################################################################                                                            
#                                 FILES                                        #                                                            
################################################################################  

S_DIR	=	sources/
SRCS	=	main.c exit_utils.c parser.c parse_utils.c map_check_player_init.c \
			game.c calculations.c keypress.c display3D.c display2D.c calc_utils.c
OBJS	=	$(addprefix $(S_DIR), $(SRCS:.c=.o))
# OBJS	=	screen_ttt2.c

################################################################################                                                            
#                                 RULES                                        #                                                            
################################################################################  

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
		@echo "Compiling sources.."
		$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) $(MFLAGS) -o $@
		@echo "Ready!"

$(LIBFT):
		@echo "Compiling libft.."
		@make -s -C libft
		@echo "Libft ready!"

$(MLX)	:
		@echo "Compiling mlx.."
		make -s -C mlx
		@echo "Mlx ready!"

clean:
		$(RM) $(OBJS)
		$(CL_MLX)
		@make $@ -s -C libft
		@echo "Removed objects"

fclean:         clean
		$(RM) $(NAME)
		@make $@ -s -C libft
		@echo "Removed executable files"

re:			fclean all

.PHONY:		re, all, clean, fclean
