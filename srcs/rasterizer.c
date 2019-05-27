/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:20:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/27 06:38:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	triangle(t_fdf_poly *t, t_fdf_image *image)
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

	t0 = (t_point){t->p0.x, t->p0.y, t->p0.z};
	t1 = (t_point){t->p1.x, t->p1.y, t->p1.z};
	t2 = (t_point){t->p2.x, t->p2.y, t->p2.z};
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
	intensity = t->normal.x * 0 + t->normal.y * 0 + t->normal.z * 0.90;
	intensity = intensity > 1 ? 1 : intensity;
	if (intensity <= 0)
		return ;
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
			if (((p.x >= 0 && p.x < WIN_WIDTH) && (p.y >= 0 && p.y < WIN_HEIGTH))
			&& (image->zbuffer[p.x + p.y * WIN_WIDTH] <= p.z) && p.z < PERSPECTIVE)
			{
				t->color = get_color(p.z, 1600, -300, (int[2]){0x00FFFF, 0xC9A0DC});
				t->color = ((int)(intensity * (t->color & 0x000000FF))
				| ((int)(intensity * ((t->color >> 8) & 0x000000FF))) << 8
				| ((int)(intensity * ((t->color >> 16) & 0x000000FF))) << 16
				| (0 << 24));
				image->zbuffer[p.x + p.y * WIN_WIDTH] = p.z;
				put_on_image(p.x, p.y, t->color, image);
			}
			j++;
		}
		i++;
	}
}
