/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 14:25:03 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/27 03:59:58 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void				ft_exit(int a)
{
	exit(a);
}

void				normalize_polylist(t_fdf_poly_list *polylist)
{
	t_fdf_poly_list	*list;
	int				mx;
	int				my;

	list = polylist;
	mx = 0;
	my = 0;
	while (list)
	{
		mx = fmax(mx, fmax(list->polygone->p0.x,
		fmax(list->polygone->p1.x, list->polygone->p2.x)));
		my = fmax(my, fmax(list->polygone->p0.y,
		fmax(list->polygone->p1.y, list->polygone->p2.y)));
		list = list->next;
	}
	list = polylist;
	while (list)
	{
		list->polygone->p0.x -= mx / 2;
		list->polygone->p1.x -= mx / 2;
		list->polygone->p2.x -= mx / 2;
		list->polygone->p0.y -= my / 2;
		list->polygone->p1.y -= my / 2;
		list->polygone->p2.y -= my / 2;
		list = list->next;
	}
}

void				window_initilize(t_fdf_window *win, char *filename)
{
	win->width = WIN_WIDTH;
	win->height = WIN_HEIGTH;
	win->mtrx_data = fdf_reader(filename);
	win->mlx = mlx_init();
	win->ptr_win = mlx_new_window(win->mlx, win->width, win->height, "FdF");
}

void				image_initilize(t_fdf_image *img)
{
	img->zbuffer = (int *)malloc(sizeof(int) * WIN_WIDTH * WIN_HEIGTH);
	img->ptr_img = mlx_new_image(img->ptr_fdf_window->mlx,
	img->ptr_fdf_window->width, img->ptr_fdf_window->height);
	img->ptr_data = mlx_get_data_addr(img->ptr_img,
	&(img->bpp), &(img->size_line), &(img->endian));
	img->offsetx = WIN_WIDTH / 2;
	img->offsety = WIN_HEIGTH / 2;
	img->anglex = 0;
	img->angley = 0;
	img->anglez = 0;
	img->scalex = 8;
	img->scaley = 8;
	img->scalez = 8;
	ft_bzero(img->ptr_data, img->size_line);
	img->polygones = create_list_of_polygones(img->ptr_fdf_window->mtrx_data, 0xDDA0DD);
	normalize_polylist(img->polygones);
}

int					main(int argc, char **argv)
{
	t_fdf_window	win_main;
	t_fdf_image		image;

	if (argc != 2)
		return (0);
	window_initilize(&win_main, argv[1]);
	image.ptr_fdf_window = &win_main;
	image_initilize(&image);
	handle_draw(&image);
	mlx_hook(win_main.ptr_win, 2, 0, rotate_handle, &image);
	mlx_hook(win_main.ptr_win, 3, 0, zoom_handle, &image);
	mlx_loop(win_main.mlx);
	return (0);
}
