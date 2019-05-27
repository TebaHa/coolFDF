/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawhandle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 08:51:16 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/27 09:20:13 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int			print_check(t_fdf_poly polygon)
{
	return (((polygon.p0.x > WIN_WIDTH && polygon.p1.x
	> WIN_WIDTH && polygon.p2.x > WIN_WIDTH)
	|| (polygon.p0.y > WIN_HEIGTH && polygon.p1.y
	> WIN_HEIGTH && polygon.p2.y > WIN_HEIGTH))
	|| ((polygon.p0.x < 0 && polygon.p1.x
	< 0 && polygon.p2.x < 0)
	|| (polygon.p0.y < 0 && polygon.p1.y
	< 0 && polygon.p2.y < 0))
	|| (polygon.p0.z >= PERSPECTIVE && polygon.p1.z
	>= PERSPECTIVE && polygon.p2.z >= PERSPECTIVE));
}

void		draw(t_fdf_poly plg, t_fdf_image *img)
{
	if (!print_check(plg))
	{
		if (img->ptr_fdf_window->info.polygones > 0)
			triangle(&plg, img);
		if (img->ptr_fdf_window->info.lines > 0)
			triangle_lines(&plg, img);
	}
}
