/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:06:49 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/20 19:07:09 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		rotate_handle(int key, void *param)
{
	t_fdf_image		*img;

	img = (t_fdf_image *)param;
	if (key == ARROW_UP)
		img->qtr = quaternion_multiply(
		rotate_around((t_point){1, 0, 0}, 10), img->qtr);
	else if (key == ARROW_DOWN)
		img->qtr = quaternion_multiply(
		rotate_around((t_point){1, 0, 0}, -10), img->qtr);
	else if (key == ARROW_LEFT)
		img->qtr = quaternion_multiply(
		rotate_around((t_point){0, 1, 0}, -10), img->qtr);
	else if (key == ARROW_RIGHT)
		img->qtr = quaternion_multiply(
		rotate_around((t_point){0, 1, 0}, 10), img->qtr);
	else if (key == Z_UP)
		img->qtr = quaternion_multiply(
		rotate_around((t_point){0, 0, 1}, -10), img->qtr);
	else if (key == Z_DOWN)
		img->qtr = quaternion_multiply(
		rotate_around((t_point){0, 0, 1}, 10), img->qtr);
	else if (key == MAIN_PAD_ESC)
		exit(1);
	handle_draw(img);
	return (0);
}

int		zoom_handle(int key, void *param)
{
	t_fdf_image		*img;

	img = (t_fdf_image *)param;
	if (key == ZOOM_IN)
		zoom_in(&img->scalex, &img->scaley, &img->scalez);
	else if (key == ZOOM_OUT)
		zoom_out(&img->scalex, &img->scaley, &img->scalez);
	handle_draw(img);
	return (0);
}

void	handle_draw(t_fdf_image *img)
{
	t_fdf_poly_list	*list;
	void			*mlx;
	void			*win_ptr;
	void			*image_ptr;

	list = img->polygones;
	ft_bzero(img->ptr_data, img->ptr_fdf_window->width
	* img->ptr_fdf_window->height * 4);
	zbuffer_init(img->zbuffer);
	rotate(img, img->polygones, img->qtr);
	mlx = img->ptr_fdf_window->mlx;
	win_ptr = img->ptr_fdf_window->ptr_win;
	image_ptr = img->ptr_img;
	mlx_put_image_to_window(mlx, win_ptr, image_ptr, 0, 0);
}
