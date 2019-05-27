/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:13:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/27 06:27:20 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	triangle_lines(t_fdf_poly *t, t_fdf_image *image)
{

	if (t->p0.y == t->p1.y && t->p0.y == t->p2.y)
		return ;
	bresenham_line(&(t->p0), &(t->p1), image, t->color);
}

void	bresenham_line(t_point *beg, t_point *end,
							t_fdf_image *image, int color)
{
	int			steep;
	double		dx;
	double		dy;
	int			error2;
	int			derror2;
	int			x;
	int			y;
	t_point		b;
	t_point		e;

	b.x = beg->x;
	b.y = beg->y;
	e.x = end->x;
	e.y = end->y;
	steep = 0;
	color = 0x8A2BE2;
	if (abs(b.x - e.x) < abs(b.y - e.y))
	{
		ft_swap(&(b.x), &(b.y));
		ft_swap(&(e.x), &(e.y));
		steep = 1;
	}
	if (b.x > e.x)
	{
		ft_swap(&(b.x), &(e.x));
		ft_swap(&(b.y), &(e.y));
	}
	dx = e.x - b.x;
	dy = e.y - b.y;
	derror2 = fabs(dy) * 2;
	error2 = 0;
	y = b.y;
	x = b.x;
	while (x <= e.x)
	{
		if (((steep && ((x >= 0 && x < WIN_HEIGTH) && (y >= 0 && y < WIN_WIDTH) &&
		(image->zbuffer[y + x * WIN_WIDTH] <= fmax(beg->z, end->z))))
		|| (!steep && ((y >= 0 && y < WIN_HEIGTH) && (x >= 0 && x < WIN_WIDTH))
		&& (image->zbuffer[x + y * WIN_WIDTH] <= fmax(beg->z, end->z))))
		&& fmax(beg->z, end->z) < PERSPECTIVE)
		{
			color = get_color(dx > dy ? steep ? y : x : steep ? x : y, 0, dx > dy ? WIN_WIDTH * 0.8 : WIN_HEIGTH * 0.8,
			(int[2]){0x00FFFF, 0xC9A0DC});
			put_on_image(steep ? y : x, steep ? x : y, color, image);
		}
		error2 += derror2;
		if (error2 > dx)
		{
			y += e.y > b.y ? 1 : -1;
			error2 -= dx * 2;
		}
		x++;
	}
}
