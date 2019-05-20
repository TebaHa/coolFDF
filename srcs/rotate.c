/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:23:32 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/20 20:58:13 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		rotate(t_fdf_image *img, t_fdf_poly_list *list, t_fdf_qterion q)
{
	t_fdf_poly_list	*t_list;
	t_fdf_poly		t_poly;

	t_list = list;
	t_poly.color = GREEN;
	while (t_list)
	{
		t_poly.p0 = project_q(&t_list->polygone->p0, q,
		(double [3]){img->scalex, img->scaley, img->scalez});
		t_poly.p1 = project_q(&t_list->polygone->p1, q,
		(double [3]){img->scalex, img->scaley, img->scalez});
		t_poly.p2 = project_q(&t_list->polygone->p2, q,
		(double [3]){img->scalex, img->scaley, img->scalez});
		t_poly.normal = calc_normal(&t_poly);
		triangle(&t_poly, img);
		triangle_lines(&t_poly, img);
		t_list = t_list->next;
	}
}
