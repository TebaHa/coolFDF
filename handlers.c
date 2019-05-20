/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 01:56:07 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/18 18:07:23 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>
#include <key_macroses.h>

int		rotate_handle(int key, void *param)
{
	t_fdf_image		*img;
	t_fdf_poly_list	*list;
	void			*mlx;
	void			*win_ptr;
	void			*image_ptr;

	img = (t_fdf_image *)param;
	ft_bzero(img->data_image, img->width * img->height * 4);
	zbuffer_init(img->zbuffer);
	if (key == ARROW_UP)
		img->window->q = quaternion_multiply(rotate_around((t_point){1, 0, 0, 0, 0}, 10),  img->window->q);
	else if (key == ARROW_DOWN)
		img->window->q = quaternion_multiply(rotate_around((t_point){1, 0, 0, 0, 0}, -10), img->window->q);
	else if (key == ARROW_LEFT)
		img->window->q = quaternion_multiply(rotate_around((t_point){0, 1, 0, 0, 0}, -10), img->window->q);
	else if (key == ARROW_RIGHT)
		img->window->q = quaternion_multiply(rotate_around((t_point){0, 1, 0, 0, 0}, 10), img->window->q);
	else if (key == Z_UP)
		img->window->q = quaternion_multiply(rotate_around((t_point){0, 0, 1, 0, 0}, -10), img->window->q);
	else if (key == Z_DOWN)
		img->window->q = quaternion_multiply(rotate_around((t_point){0, 0, 1, 0, 0}, 10), img->window->q);
	else if (key == MAIN_PAD_ESC)
		exit(1);
	handle_draw(img);
	return (0);
}

int		zoom_handle(int key, void *param)
{
	t_fdf_poly_list	*list;
	t_fdf_image		*img;

	img = (t_fdf_image *)param;
	ft_bzero(img->data_image, img->width * img->height * 4);
	zbuffer_init(img->zbuffer);
	if (key == ZOOM_IN)
		zoom_in(img->window->polygone_list);
	else if (key == ZOOM_OUT)
		zoom_out(img->window->polygone_list);
	else if (key == LINES)
		img->window->wininfo.lines = -img->window->wininfo.lines;
	else if (key == POLYGONES)
		img->window->wininfo.polygones = -img->window->wininfo.polygones;
	handle_draw(img);
	return (0);
}

void	handle_draw(t_fdf_image * img)
{
	t_fdf_poly_list	*list;
	void			*mlx;
	void			*win_ptr;
	void			*image_ptr;

	list = img->window->polygone_list;
	find_offset_polylist(img->window->polygone_list, &(img->offsety), &(img->offsety));
	rotate(img, img->window->polygone_list, img->window->q);
	mlx = img->window->mlx;
	win_ptr = img->window->win_ptr;
	image_ptr = img->ptr_image;
	mlx_put_image_to_window(mlx, win_ptr, image_ptr, 0, 0);
	info(img->window);
}
