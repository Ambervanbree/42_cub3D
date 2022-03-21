# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 14:51:08 by avan-bre          #+#    #+#              #
#    Updated: 2022/03/21 17:10:42 by cproesch         ###   ########.fr        #
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

# S_DIR	=	sources/
# SRCS	=	main.c parser.c exit_utils.c parse_utils.c map_checker.c \
# 			display_game.c \
# OBJS	=	$(addprefix $(S_DIR), $(SRCS:.c=.o))
OBJS	=	screen_test.c

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
