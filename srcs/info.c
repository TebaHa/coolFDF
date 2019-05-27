/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 08:48:21 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/27 09:16:29 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		put_info(t_fdf_image *img)
{
	if (img->ptr_fdf_window->info.lines > 0)
		mlx_string_put(img->ptr_fdf_window->mlx,
		img->ptr_fdf_window->ptr_win, 10, 10, WHITE, "1. LINES");
	else
		mlx_string_put(img->ptr_fdf_window->mlx,
		img->ptr_fdf_window->ptr_win, 10, 10, RED, "1. LINES");
	if (img->ptr_fdf_window->info.polygones > 0)
		mlx_string_put(img->ptr_fdf_window->mlx,
		img->ptr_fdf_window->ptr_win, 10, 30, WHITE, "2. POLYGONES");
	else
		mlx_string_put(img->ptr_fdf_window->mlx,
		img->ptr_fdf_window->ptr_win, 10, 30, RED, "2. POLYGONES");
	if (img->ptr_fdf_window->info.perspective > 0)
		mlx_string_put(img->ptr_fdf_window->mlx,
		img->ptr_fdf_window->ptr_win, 10, 50, WHITE, "3. PERSPECTIVE");
	else
		mlx_string_put(img->ptr_fdf_window->mlx,
		img->ptr_fdf_window->ptr_win, 10, 50, RED, "3. PERSPECTIVE");
}
