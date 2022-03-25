#include	"mlx_int.h"

int		mlx_get_screen_size(void *twod_mlx, int *sizex, int *sizey)
{
	XWindowAttributes	xwAttr;
	Status				ret;
	t_xvar				*xvar;
	
	xvar = twod_mlx;
	ret = XGetWindowAttributes(xvar->display, xvar->root, &xwAttr);
	(*sizex) = xwAttr.width;
	(*sizey) = xwAttr.height;
}
