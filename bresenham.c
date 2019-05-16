/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 21:54:29 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/15 17:58:44 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

void	triangle_lines(t_fdf_poly *t, t_fdf_image *image, double offsetx, double offsety)
{

	if (t->p0.y == t->p1.y && t->p0.y == t->p2.y)
		return ;
	bresenham_line(&(t->p0), &(t->p1), image, t->color, offsetx, offsety);
}

void	bresenham_line(t_point *beg, t_point *end, t_fdf_image *image, int color, int offsetx, int offsety)
{
	int			steep;
	double		dx;
	double		dy;
	int			error2;
	int			derror2;
	int			zerror2;
	int			dzerror2;
	int			ystep;
	int			x;
	int			y;
	int			z;
	t_point		b;
	t_point		e;

	b.x = beg->x + offsetx;
	b.y = beg->y + offsety;
	e.x = end->x + offsetx;
	e.y = end->y + offsety;
	steep = 0;
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
		if (((steep && ((x > 0 && x < WIN_HEIGTH) && (y > 0 && y < WIN_WIDTH)))
		|| (!steep && ((y > 0 && y < WIN_HEIGTH) && (x > 0 && x < WIN_WIDTH)))))
			put_on_image(steep ? y : x, steep ? x : y, 0x8A2BE2,  image);
		error2 += derror2;
		if (error2 > dx)
		{
			y += e.y > b.y ? 1 : -1;
			error2 -= dx * 2;
		}
		x++;
	}
}

