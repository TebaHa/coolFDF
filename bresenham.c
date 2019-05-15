/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 21:54:29 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/14 20:06:53 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

void	ft_swap(int  *a, int *b)
{
	int tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

void	point_swap(t_point *t0, t_point *t1)
{
	t_point		tmp;

	tmp.x = t0->x;
	tmp.y = t0->y;
	tmp.z = t0->z;
	tmp.color = t0->color;
	t0->x = t1->x;
	t0->y = t1->y;
	t0->z = t1->z;
	t0->color = t1->color;
	t1->x = tmp.x;
	t1->y = tmp.y;
	t1->z = tmp.z;
	t1->color = tmp.color;
}

int		ft_abs(int num)
{
	return (num > 0 ? num : -num);
}

void	put_on_image(int x, int y, int color, t_fdf_image *image)
{
	size_t	offset;

	offset = x * 4 + 4 * image->width * y;
	(image->data_image)[offset] = (char)(color);
	(image->data_image)[offset + 1] = (char)(color >> 8);
	(image->data_image)[offset + 2] = (char)(color >> 16);
	(image->data_image)[offset + 3] = (char)(color >> 24);
}

void	triangle(t_fdf_poly *t, t_fdf_image *image, int offsetx, int offsety)
{
	int			total_height;
	int			second_half;
	int			i;
	int			j;
	int			segment_height;
	t_point		A;
	t_point		B;
	t_point		t0;
	t_point		t1;
	t_point		t2;
	double		alpha;
	double		beta;
	double		intensity;
	double		phi;
	t_point		p;

	t0 = (t_point){t->p0.x + offsetx, t->p0.y + offsety, t->p0.z, 0, 0};
	t1 = (t_point){t->p1.x + offsetx, t->p1.y + offsety, t->p1.z, 0, 0};
	t2 = (t_point){t->p2.x + offsetx, t->p2.y + offsety, t->p2.z, 0, 0};
	if (t0.y == t1.y && t0.y == t2.y)
		return ;
	if (t0.y > t1.y)
		point_swap(&(t0), &(t1));
	if (t0.y > t2.y)
		point_swap(&(t0), &(t2));
	if (t1.y > t2.y)
		point_swap(&(t1), &(t2));
	total_height = (t2.y) - (t0.y);
	i = 0;
	intensity = t->normal->x * 1 + t->normal->y * 1 + t->normal->z * -1;
	intensity = intensity > 1 ? 1 : intensity < 0 ? 0 : intensity;
	//if (intensity < 0)
	//	return ;
	t->color =  ((int)(intensity * 255)) | ((int)(intensity * 255)) << 8 | ((int)(intensity * 255)) << 16 | (0 << 24);
	while (i < total_height)
	{
		second_half = i > t1.y - t0.y || t1.y == t0.y;
		segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
		alpha = (double)i / total_height;
		beta = (double)(i - (second_half ? t1.y - t0.y : 0)) / segment_height;
		A.x = t0.x + (t2.x - t0.x) * alpha;
		A.y = t0.y + (t2.y - t0.y) * alpha;
		A.z = t0.z + (t2.z - t0.z) * alpha;
		B.x = second_half ? t1.x + (t2.x - t1.x) * beta : t0.x + (t1.x - t0.x) * beta;
		B.y = second_half ? t1.y + (t2.y - t1.y) * beta : t0.y + (t1.y - t0.y) * beta;
		B.z = second_half ? t1.z + (t2.z - t1.z) * beta : t0.z + (t1.z - t0.z) * beta;
		if (A.x > B.x)
			point_swap(&A, &B);
		j = A.x;
		while (j <= B.x)
		{
			phi = B.x == A.x ? 1.0 : (double)(j - A.x) / (double)(B.x - A.x);
			p.x = A.x + (B.x - A.x) * phi;
			p.y = A.y + (B.y - A.y) * phi;
			p.z = A.z + (B.z - A.z) * phi;
			if (((p.x > 0 && p.x < WIN_WIDTH) && (p.y > 0 && p.y < WIN_HEIGTH))
			&& (image->zbuffer[p.x + p.y * WIN_WIDTH] < p.z))
			{
				image->zbuffer[p.x + p.y * WIN_WIDTH] = p.z;
				put_on_image(p.x, p.y, t->color, image);
			}
			j++;
		}
		i++;
	}
}

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
	if (ft_abs(b.x - e.x) < ft_abs(b.y - e.y))
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
	derror2 = ft_abs(dy) * 2;
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

