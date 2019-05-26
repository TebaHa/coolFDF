/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:23:32 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/26 18:28:00 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_point		perspective(t_point a, int c)
{
	t_fdf_vec4	res;
	t_fdf_mat4	mt4;

	mt4 = getzeroaffinmat4();
	mt4.values[3][2] -= (double)(1.0 / (double)c);
	res = matrix_on_vec_multiply(mt4,
	(t_fdf_vec4){(double)a.x, (double)a.y, (double)a.z, 1.0});
	a.x = res.x / res.w;
	a.y = res.y / res.w;
	a.z = res.z / res.w;
	a.x += WIN_WIDTH / 2;
	a.y += WIN_HEIGTH / 2;
	return (a);
}

void		rotate(t_fdf_image *img, t_fdf_poly_list *list, t_fdf_qternion q)
{
	t_fdf_poly_list	*t_list;
	t_fdf_poly		t_poly;

	t_list = list;
	t_poly.color = GREEN;
	while (t_list)
	{
		t_poly.p0 = project_q(&t_list->polygone->p0, q,
		(double[3]){img->scalex, img->scaley, img->scalez});
		t_poly.p1 = project_q(&t_list->polygone->p1, q,
		(double[3]){img->scalex, img->scaley, img->scalez});
		t_poly.p2 = project_q(&t_list->polygone->p2, q,
		(double[3]){img->scalex, img->scaley, img->scalez});
		t_poly.p0 = perspective(t_poly.p0, 1600);
		t_poly.p1 = perspective(t_poly.p1, 1600);
		t_poly.p2 = perspective(t_poly.p2, 1600);
		t_poly.normal = calc_normal(&t_poly);
		//triangle(&t_poly, img);
		triangle_lines(&t_poly, img);
		t_list = t_list->next;
	}
}
