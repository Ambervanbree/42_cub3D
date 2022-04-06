# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 14:51:08 by avan-bre          #+#    #+#              #
#    Updated: 2022/04/06 15:35:43 by cproesch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################                                                            
#                                 EXECUTBLES                                   #                                                            
################################################################################ 

OS		=	$(shell uname -s)
NAME	=	cub3D
BONUS	=	cub3D_b
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
	MLX		=	mlx/libmlx_Linux.a
else
	MLX		=
endif

IFLAGS	=	-I. -Ilibft -Imlx
CFLAGS	=	-Wall -Werror -Wextra $(IFLAGS) $(SFLAGS)
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
B_DIR	=	bonus/
C_SRCS	=	parser.c parse_utils.c map_check_player_init.c calculations.c \
			keypress.c display3D.c calc_utils.c display3D_utils.c
SRCS	=	$(C_SRCS) main.c game.c exit_utils.c
SRCS_B	=	display2D.c exit_utils_bonus.c game_bonus.c main_bonus.c
B_SRCS	=	$(addprefix $(S_DIR), $(C_SRCS)) $(addprefix $(B_DIR), $(SRCS_B))
OBJS	=	$(addprefix $(S_DIR), $(SRCS:.c=.o))
B_OBJS	=	$(B_SRCS:.c=.o)

################################################################################                                                            
#                                 RULES                                        #                                                            
################################################################################  

all:		$(NAME)

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
		@echo "Compiling sources.."
		$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) $(MFLAGS) -o $@
		@echo "Ready!"

%.o:	%.c
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(BONUS):	$(LIBFT) $(MLX) $(B_OBJS)
		@echo "Compiling sources.."
		$(CC) $(B_OBJS) $(CFLAGS) $(LFLAGS) $(MFLAGS) -o $@
		@echo "Ready!"

bonus:	$(BONUS)

$(LIBFT):
		@echo "Compiling libft.."
		make -s -C libft
		@echo "Libft ready!"

$(MLX)	:
		@echo "Compiling mlx.."
		make -s -C mlx
		@echo "Mlx ready!"

clean:
		$(RM) $(OBJS) $(B_OBJS)
		$(CL_MLX)
		@make $@ -s -C libft
		@echo "Removed objects"

fclean:         clean
		$(RM) $(NAME) $(BONUS)
		@make $@ -s -C libft
		@echo "Removed executable files"

re:			fclean all

.PHONY:		re, all, clean, fclean
