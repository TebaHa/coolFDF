/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 01:54:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/15 12:16:01 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

int			ch_in_disp(int x0, int mx)
{
	return (mx <= x0);
}

void		rotate(t_fdf_image * img, t_fdf_poly_list *list, t_fdf_c_terion q)
{
	t_fdf_poly_list	*t_list;
	t_fdf_poly		t_poly;

	t_list = list;
	t_poly.color = GREEN;
	while (t_list)
	{
		t_poly.p0 = project_q(&t_list->polygone->p0, q);
		t_poly.p1 = project_q(&t_list->polygone->p1, q);
		t_poly.p2 = project_q(&t_list->polygone->p2, q);
		t_poly.normal = calc_normal(&t_poly);
		if (img->window->wininfo.polygones > 0)
			triangle(&t_poly, img, 0, 0);
		if (img->window->wininfo.lines > 0)
			triangle_lines(&t_poly, img, 0, 0);
		free(t_poly.normal);
		t_list = t_list->next;
	}
}
