/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:23:32 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/27 06:00:46 by zytrams          ###   ########.fr       */
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

void		rotate(t_fdf_image *img, t_fdf_poly_list *list, t_fdf_qternion q)
{
	t_fdf_poly_list	*t_list;
	t_fdf_poly		t_poly;

	t_list = list;
	while (t_list)
	{
		t_poly.p0 = project_q(&t_list->polygone->p0, q,
		(double[3]){img->scalex, img->scaley, img->scalez});
		t_poly.p1 = project_q(&t_list->polygone->p1, q,
		(double[3]){img->scalex, img->scaley, img->scalez});
		t_poly.p2 = project_q(&t_list->polygone->p2, q,
		(double[3]){img->scalex, img->scaley, img->scalez});
		t_poly.p0 = perspective(t_poly.p0, PERSPECTIVE + 100);
		t_poly.p1 = perspective(t_poly.p1, PERSPECTIVE + 100);
		t_poly.p2 = perspective(t_poly.p2, PERSPECTIVE + 100);
		t_poly.normal = calc_normal(&t_poly);
		t_poly.color = t_list->polygone->color;
		if (!print_check(t_poly))
		{
			triangle(&t_poly, img);
			triangle_lines(&t_poly, img);
		}
		t_list = t_list->next;
	}
}
