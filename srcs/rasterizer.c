/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:20:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/06/04 16:01:11 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	triangle(t_fdf_poly *t, t_fdf_image *image)
{
	t_triangle	trg;

	trg.t0 = (t_point){t->p0.x, t->p0.y, t->p0.z};
	trg.t1 = (t_point){t->p1.x, t->p1.y, t->p1.z};
	trg.t2 = (t_point){t->p2.x, t->p2.y, t->p2.z};
	if (trg.t0.y == trg.t1.y && trg.t0.y == trg.t2.y)
		return ;
	if (trg.t0.y > trg.t1.y)
		point_swap(&(trg.t0), &(trg.t1));
	if (trg.t0.y > trg.t2.y)
		point_swap(&(trg.t0), &(trg.t2));
	if (trg.t1.y > trg.t2.y)
		point_swap(&(trg.t1), &(trg.t2));
	trg.total_height = (trg.t2.y) - (trg.t0.y);
	trg.i = 0;
	trg.intensity = t->normal.x * 0 + t->normal.y * 0 + t->normal.z * 0.90;
	trg.intensity = trg.intensity > 1 ? 1 : trg.intensity;
	if (trg.intensity <= 0)
		return ;
	while (trg.i < trg.total_height)
	{
		trg.second_half = trg.i > trg.t1.y -trg.t0.y || trg.t1.y == trg.t0.y;
		trg.segment_height = trg.second_half ? trg.t2.y - trg.t1.y : trg.t1.y - trg.t0.y;
		trg.alpha = (double)trg.i / trg.total_height;
		trg.beta = (double)(trg.i - (trg.second_half ? trg.t1.y - trg.t0.y : 0)) / trg.segment_height;
		trg.a.x = trg.t0.x + (trg.t2.x - trg.t0.x) * trg.alpha;
		trg.a.y = trg.t0.y + (trg.t2.y - trg.t0.y) * trg.alpha;
		trg.a.z = trg.t0.z + (trg.t2.z - trg.t0.z) * trg.alpha;
		trg.b.x = trg.second_half ? trg.t1.x + (trg.t2.x - trg.t1.x) * trg.beta : trg.t0.x + (trg.t1.x - trg.t0.x) * trg.beta;
		trg.b.y = trg.second_half ? trg.t1.y + (trg.t2.y - trg.t1.y) * trg.beta : trg.t0.y + (trg.t1.y - trg.t0.y) * trg.beta;
		trg.b.z = trg.second_half ? trg.t1.z + (trg.t2.z - trg.t1.z) * trg.beta : trg.t0.z + (trg.t1.z - trg.t0.z) * trg.beta;
		if (trg.a.x > trg.b.x)
			point_swap(&trg.a, &trg.b);
		trg.j = trg.a.x;
		while (trg.j <= trg.b.x)
		{
			trg.phi = trg.b.x == trg.a.x ? 1.0 : (double)(trg.j - trg.a.x) / (double)(trg.b.x - trg.a.x);
			trg.p.x = trg.a.x + (trg.b.x - trg.a.x) * trg.phi;
			trg.p.y = trg.a.y + (trg.b.y - trg.a.y) * trg.phi;
			trg.p.z = trg.a.z + (trg.b.z - trg.a.z) * trg.phi;
			if (((trg.p.x >= 0 && trg.p.x < WIN_WIDTH) && (trg.p.y >= 0 && trg.p.y < WIN_HEIGTH))
			&& (image->zbuffer[trg.p.x + trg.p.y * WIN_WIDTH] <= trg.p.z) && trg.p.z < PERSPECTIVE)
			{
				t->color = get_color(trg.p.z, 1600, -300, (int[2]){0x00FFFF, 0xC9A0DC});
				t->color = ((int)(trg.intensity * (t->color & 0x000000FF))
				| ((int)(trg.intensity * ((t->color >> 8) & 0x000000FF))) << 8
				| ((int)(trg.intensity * ((t->color >> 16) & 0x000000FF))) << 16
				| (0 << 24));
				image->zbuffer[trg.p.x + trg.p.y * WIN_WIDTH] = trg.p.z;
				put_on_image(trg.p.x, trg.p.y, t->color, image);
			}
			trg.j++;
		}
		trg.i++;
	}
}
