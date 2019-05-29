/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:13:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/29 17:15:51 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		triangle_lines(t_fdf_poly *t, t_fdf_image *image)
{

	if (t->p0.y == t->p1.y && t->p0.y == t->p2.y)
		return ;
	bresenham_line(&(t->p0), &(t->p1), image, t->color);
}

void		swapper(t_point *a, t_point *b, int *steep)
{
	*steep = 0;
	if (abs(a->x - b->x) < abs(a->y - b->y))
	{
		ft_swap(&(a->x), &(a->y));
		ft_swap(&(b->x), &(b->y));
		*steep = 1;
	}
	if (a->x > b->x)
	{
		ft_swap(&(a->x), &(b->x));
		ft_swap(&(a->y), &(b->y));
	}
}

t_bcontex	bresenham_init(t_point *beg, t_point *end)
{
	t_bcontex	c;

	c.b.x = beg->x;
	c.b.y = beg->y;
	c.e.x = end->x;
	c.e.y = end->y;
	swapper(&c.b, &c.e, &c.steep);
	c.dx = c.e.x - c.b.x;
	c.dy = c.e.y - c.b.y;
	c.derror2 = fabs(c.dy) * 2;
	c.error2 = 0;
	c.y = c.b.y;
	c.x = c.b.x;
	return (c);
}

void		bresenham_put_pixel(t_bcontex *c,
								t_fdf_image *image, int color, int zmax)
{
	if (((c->steep && ((c->x >= 0 && c->x < WIN_HEIGTH)
	&& (c->y >= 0 && c->y < WIN_WIDTH) &&
	(image->zbuffer[c->y + c->x * WIN_WIDTH] < zmax + 1)))
	|| (!c->steep && ((c->y >= 0 && c->y < WIN_HEIGTH)
	&& (c->x >= 0 && c->x < WIN_WIDTH))
	&& (image->zbuffer[c->x + c->y * WIN_WIDTH] < zmax + 1)))
	&& zmax < PERSPECTIVE)
	{
		if (c->dx >= c->dy)
			color = get_color(c->steep ? c->y : c->x,
			0, WIN_WIDTH * 0.8, (int[2]){0x00FFFF, 0xC9A0DC});
		else
			color = get_color(c->steep ? c->x : c->y,
			0, WIN_HEIGTH * 0.8, (int[2]){0x00FFFF, 0xC9A0DC});
		put_on_image(c->steep ? c->y : c->x,
		c->steep ? c->x : c->y, color, image);
	}
}

void		bresenham_line(t_point *beg, t_point *end,
							t_fdf_image *image, int color)
{
	t_bcontex	c;

	c = bresenham_init(beg, end);
	while (c.x <= c.e.x)
	{
		bresenham_put_pixel(&c, image, color, fmax(beg->z, end->z));
		c.error2 += c.derror2;
		if (c.error2 > c.dx)
		{
			c.y += c.e.y > c.b.y ? 1 : -1;
			c.error2 -= c.dx * 2;
		}
		c.x++;
	}
}
