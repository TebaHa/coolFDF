/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:06:49 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/27 05:10:16 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void				rotate_helper(t_fdf_image *img)
{
	img->qtr = quaternion_multiply(
		rotate_around((t_point){0, 0, 1}, img->anglez), img->qtr);
	img->qtr = quaternion_multiply(
		rotate_around((t_point){1, 0, 0}, img->anglex), img->qtr);
	img->qtr = quaternion_multiply(
		rotate_around((t_point){0, 1, 0}, img->angley), img->qtr);
}

int					rotate_handle(int key, void *param)
{
	t_fdf_image		*img;

	img = (t_fdf_image *)param;
	img->qtr = (t_fdf_qternion){0, 0, 0, 1};
	if (key == ARROW_UP)
		img->anglex += 5;
	else if (key == ARROW_DOWN)
		img->anglex -= 5;
	if (key == ARROW_LEFT)
		img->angley -= 5;
	else if (key == ARROW_RIGHT)
		img->angley += 5;
	if (key == Z_UP)
		img->anglez += 5;
	else if (key == Z_DOWN)
		img->anglez -= 5;
	if (key == MAIN_PAD_ESC)
		exit(1);
	rotate_helper(img);
	handle_draw(img);
	return (0);
}

int					zoom_handle(int key, void *param)
{
	t_fdf_image		*img;

	img = (t_fdf_image *)param;
	if (key == ZOOM_IN)
		zoom_in(&img->scalex, &img->scaley, &img->scalez);
	else if (key == ZOOM_OUT)
		zoom_out(&img->scalex, &img->scaley, &img->scalez);
	else if (key == LINES)
		img->ptr_fdf_window->info.lines *= -1;
	else if (key == PERSP)
		img->ptr_fdf_window->info.perspective *= -1;
	else if (key == POLYGONES)
		img->ptr_fdf_window->info.polygones *= -1;
	handle_draw(img);
	return (0);
}

void				handle_draw(t_fdf_image *img)
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
	put_info(img);
}
