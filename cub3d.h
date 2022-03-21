/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:49:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/21 19:13:28 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PIC_BACK "./images/floor.xpm"
# define PIC_WALL "./images/wall3.xpm"
# define PI 3.14159265358979323846

enum e_enum
{
	ESC = 65307,
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	RIGHT = 65363,
	LEFT = 65361
};

typedef double	t_vector[2];

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*floor_tile;
	void	*wall_tile;
}	t_game;

typedef struct s_player
{
	int			set;
	t_vector	pos;
	t_vector	dir;
	t_vector	nextX;
	t_vector	nextY;
	double		angle;
	double		plane;
	double		dist;
	double		sdX;
	double		sdY;
	double		ddX;
	double		ddY;
	double		plane_right_X;
	double		plane_right_Y;
	double		plane_left_X;
	double		plane_left_Y;
	double		sideDist_X_X;
	double		sideDist_X_Y;
	double		sideDist_Y_X;
	double		sideDist_Y_Y;

}	t_player;

typedef struct s_map
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				height;
	int				width;
	int				*floor;
	int				*ceiling;
	char			**map;
}	t_map;

typedef struct s_data
{
	t_game		*game;
	t_player	*player;
	t_map		*map;
}	t_data;

//exit and free functions
void	free_and_exit(t_data *data, int exit_code);
int		error_message(char *string, char *name, int code);
void	free_string(char **string);
void	ft_free_map(t_map *map);

//parser
int		parse_init_map(t_map *map, char *file);
char	*get_path_texture(char *line);
int		*get_color(char *line);
void	print_map(t_map *map);
void	get_len(t_map *map, int fd);
char	*realloc_line(char *line, int size);
int		check_map_init_player(t_data *data);

//game play
void	init_game(t_data *data);
int		key_event(int keypress, t_data *data);
void	get_view_points(t_player *player);

#endif