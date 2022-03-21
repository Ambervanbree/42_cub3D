#include "cub3d.h"

#define CEILING 0x00ffff
#define FLOOR   0x00ff00
#define WALL    0x999999

typedef struct s_test
{
    void	*mlx_ptr;
	void	*win_ptr;
    int     win_nb_x;
    int     win_nb_y;
    int     wall[800];
}   t_test;

int	redcross_exit(void)
{
	exit(0);
    return (0);
}

int	key_event(int keypress)
{
	if (keypress == ESC)
		exit(0);
	return (0);
}

int screen_display(void)
{
    printf("coucou\n");
    return (0);
}

void    init_wall(t_test *test)
{
    int x;

    x = 0;
    while (x < 800)
    {
        if (x < 400)
            test->wall[x] = 200;
        else
            test->wall[x] = 300;
        x++;
    }
}

int main(void)
{
    t_test  test;
    int     x;
    int     y;

    test.win_nb_x = 800;
    test.win_nb_y = 600;
    test.mlx_ptr = mlx_init(&test);
	test.win_ptr = mlx_new_window(test.mlx_ptr, test.win_nb_x, test.win_nb_y, "cub3D");
    init_wall(&test);
    // mlx_put_image_to_window (test.mlx_ptr, test.win_ptr, mlx_xpm_file_to_image(test.mlx_ptr, "./images/ceiling.xpm", &test.win_nb_x, &micuisse), 0, 0);
    // mlx_put_image_to_window (test.mlx_ptr, test.win_ptr, mlx_xpm_file_to_image(test.mlx_ptr, "./images/floor2.xpm", &test.win_nb_x, &micuisse), 0, 300 * 60);
    y = 0;
    while (y < test.win_nb_y / 2)
    {
        x = -1;
        while (++x < test.win_nb_x)
        {
            if (y < (test.win_nb_y / 2 - test.wall[x] / 2))
                mlx_pixel_put(test.mlx_ptr, test.win_ptr, x, y, CEILING);
            else
                mlx_pixel_put(test.mlx_ptr, test.win_ptr, x, y, WALL);
        }
        y++;
    }
    while (y < test.win_nb_y)
    {
        x = -1;
        while (++x < test.win_nb_x)
        {
            if (y > (test.win_nb_y / 2 + test.wall[x] / 2))
                mlx_pixel_put(test.mlx_ptr, test.win_ptr, x, y, FLOOR);
            else
                mlx_pixel_put(test.mlx_ptr, test.win_ptr, x, y, WALL);
        }
        y++;
    }
    mlx_loop_hook(test.mlx_ptr, &screen_display, NULL);
    mlx_hook(test.win_ptr, 2, 1L<<0, &key_event, NULL);
    mlx_hook(test.win_ptr, 17, 0, &redcross_exit, NULL);
    mlx_loop(test.mlx_ptr);
    return (0);
}