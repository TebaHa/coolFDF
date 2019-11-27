/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:23:32 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/27 05:16:46 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		resize(t_fdf_poly *plg)
{
	plg->p0.x += WIN_WIDTH / 2;
	plg->p0.y += WIN_HEIGTH / 2;
	plg->p1.x += WIN_WIDTH / 2;
	plg->p1.y += WIN_HEIGTH / 2;
	plg->p2.x += WIN_WIDTH / 2;
	plg->p2.y += WIN_HEIGTH / 2;
}

t_point		perspective(t_point a, int c)
{
	t_fdf_vec4	res;
	t_fdf_mat4	mt4;

	mt4 = getzeroaffinmat4();
	mt4.values[3][2] -= (float)(1.0 / (float)c);
	res = matrix_on_vec_multiply(mt4,
	(t_fdf_vec4){(float)a.x, (float)a.y, (float)a.z, 1.0});
	a.x = res.x / res.w;
	a.y = res.y / res.w;
	a.z = res.z / res.w;
	return (a);
}

void		rotate(t_fdf_image *img, t_fdf_poly_list *list, t_fdf_qternion q)
{
	t_fdf_poly_list	*t_list;
	t_fdf_poly		t_poly;

	t_list = list;
	while (t_list)
	{
		t_poly.p0 = calc_point(&t_list->polygone->p0, q,
		(float[3]){img->scalex, img->scaley, img->scalez});
		t_poly.p1 = calc_point(&t_list->polygone->p1, q,
		(float[3]){img->scalex, img->scaley, img->scalez});
		t_poly.p2 = calc_point(&t_list->polygone->p2, q,
		(float[3]){img->scalex, img->scaley, img->scalez});
		if (img->ptr_fdf_window->info.perspective > 0)
		{
			t_poly.p0 = perspective(t_poly.p0, PERSPECTIVE + 100);
			t_poly.p1 = perspective(t_poly.p1, PERSPECTIVE + 100);
			t_poly.p2 = perspective(t_poly.p2, PERSPECTIVE + 100);
		}
		resize(&t_poly);
		t_poly.normal = calc_normal(&t_poly);
		t_poly.color = t_list->polygone->color;
		t_poly.pos_status = t_list->polygone->pos_status;
		draw(t_poly, img);
		t_list = t_list->next;
	}
}
