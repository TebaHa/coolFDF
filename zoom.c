/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 14:42:38 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/14 13:53:20 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

int		zoom_check(t_point a, t_point b)
{
	return (abs(a.x - b.x) > 5);
}

void	zoom_in(t_fdf_poly_list *polylist)
{
	t_fdf_poly_list	*plist;
	double			tmp;

	plist = polylist;
	while (plist)
	{
		tmp = (double)plist->polygone->p0.x * 2;
		plist->polygone->p0.x = (int)tmp;
		tmp = (double)plist->polygone->p1.x * 2;
		plist->polygone->p1.x = (int)tmp;
		tmp = (double)plist->polygone->p2.x * 2;
		plist->polygone->p2.x = (int)tmp;
		tmp = (double)plist->polygone->p0.y * 2;
		plist->polygone->p0.y = (int)tmp;
		tmp = (double)plist->polygone->p1.y * 2;
		plist->polygone->p1.y = (int)tmp;
		tmp = (double)plist->polygone->p2.y * 2;
		plist->polygone->p2.y = (int)tmp;
		tmp = (double)plist->polygone->p0.z * 2;
		plist->polygone->p0.z = (int)tmp;
		tmp = (double)plist->polygone->p1.z * 2;
		plist->polygone->p1.z = (int)tmp;
		tmp = (double)plist->polygone->p2.z * 2;
		plist->polygone->p2.z = (int)tmp;
		plist = plist->next;
	}
}

void	zoom_out(t_fdf_poly_list *polylist)
{
	t_fdf_poly_list	*plist;
	double			tmp;

	plist = polylist;
	if (zoom_check(plist->polygone->p0, plist->polygone->p1))
	{
		while (plist)
		{
			tmp = (double)plist->polygone->p0.x / 2;
			plist->polygone->p0.x = (int)tmp;
			tmp = (double)plist->polygone->p1.x / 2;
			plist->polygone->p1.x = (int)tmp;
			tmp = (double)plist->polygone->p2.x / 2;
			plist->polygone->p2.x = (int)tmp;
			tmp = (double)plist->polygone->p0.y / 2;
			plist->polygone->p0.y = (int)tmp;
			tmp = (double)plist->polygone->p1.y / 2;
			plist->polygone->p1.y = (int)tmp;
			tmp = (double)plist->polygone->p2.y / 2;
			plist->polygone->p2.y = (int)tmp;
			tmp = (double)plist->polygone->p0.z / 2;
			plist->polygone->p0.z = (int)tmp;
			tmp = (double)plist->polygone->p1.z / 2;
			plist->polygone->p1.z = (int)tmp;
			tmp = (double)plist->polygone->p2.z / 2;
			plist->polygone->p2.z = (int)tmp;
			plist = plist->next;
		}
	}
}
