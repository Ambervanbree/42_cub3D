/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:49:29 by avan-bre          #+#    #+#             */
/*   Updated: 2022/03/30 17:57:09 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PIC_BACK "./images/floor3.xpm"
# define PIC_WALL "./images/wall.xpm"
# define NAME "./images/name.xpm"
# define SCR_WIDTH 800
# define SCR_HEIGHT 600
# define PI 3.14159265358979323846
# define CEILING 0x00ffff
# define FLOOR 0x00ff00
# define WALL 0x999999

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

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		end;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_img	*img3D;
	t_img	*img2D;
	void	*twod_mlx;
	void	*twod_win;
	void	*floor_tile;
	void	*wall_tile;
	void	*name;
	float	*twod_ray;
	void	*threed_mlx;
	void	*threed_win;
    int     pix_nb_x;
    int     pix_nb_y;
	float	*threed_ray;
}	t_game;

typedef struct s_player
{
	int			set;
	t_vector	pos;
	t_vector	dir;
	t_vector	*next_hit;
	double		angle;
	double		ray_angle;
	double		plane;
	double		dist;
	double		sdX;
	double		sdY;
	double		ddX;
	double		ddY;
	t_vector	*ray_x;
	t_vector	*ray_y;
}	t_player;

typedef struct s_map
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				height;
	int				width;
	int				floor;
	int				ceiling;
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
int		get_color(char *line);
void	print_map(t_map *map);
void	get_len(t_map *map, int fd);
char	*realloc_line(char *line, int size);
int		check_map_init_player(t_data *data);

//game play
//int		init_game(t_data *data, t_game *game);
int		init_game(t_data *data, t_game *game);
int		key_event(int keypress, t_data *data);
void	get_view_points(t_player *player, t_map *map, t_game *game);
double	correct_angle(double angle);
int		display(t_data *data);
void	draw_3d_game(t_data *data, t_game *game, t_img *img);
void	fish_eye_correction(t_player *player);
void	draw_2d_game(t_data *data, t_game *game);

#endif