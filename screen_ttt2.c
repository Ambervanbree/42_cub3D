#include "cub3d.h"

#define CEILING 0x00ffff
#define FLOOR   0x00ff00
#define WALL    0x999999

typedef struct s_test
{
    void	*threed_mlx;
	void	*twod_win;
    int     pix_nb_x;
    int     pix_nb_y;
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

    test.pix_nb_x = 800;
    test.pix_nb_y = 600;
    test.threed_mlx = mlx_init(&test);
	test.twod_win = mlx_new_window(test.threed_mlx, test.pix_nb_x, test.pix_nb_y, "cub3D");
    init_wall(&test);
    y = 0;
    while (y < test.pix_nb_y / 2)
    {
        x = -1;
        while (++x < test.pix_nb_x)
        {
            if (y < (test.pix_nb_y / 2 - test.wall[x] / 2))
                mlx_pixel_put(test.threed_mlx, test.twod_win, x, y, CEILING);
            else
                mlx_pixel_put(test.threed_mlx, test.twod_win, x, y, WALL);
        }
        y++;
    }
    while (y < test.pix_nb_y)
    {
        x = -1;
        while (++x < test.pix_nb_x)
        {
            if (y > (test.pix_nb_y / 2 + test.wall[x] / 2))
                mlx_pixel_put(test.threed_mlx, test.twod_win, x, y, FLOOR);
            else
                mlx_pixel_put(test.threed_mlx, test.twod_win, x, y, WALL);
        }
        y++;
    }
    // mlx_loop_hook(test.threed_mlx, &screen_display, NULL);
    // mlx_hook(test.twod_win, 2, 1L<<0, &key_event, NULL);
    // mlx_hook(test.twod_win, 17, 0, &redcross_exit, NULL);
    // mlx_loop(test.threed_mlx);
    return (0);
}