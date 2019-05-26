/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygonizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:29:02 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/21 18:42:07 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void				point_cpy(t_point *to, t_point *from)
{
	to->x = from->x;
	to->y = from->y;
	to->z = from->z;
}

t_fdf_poly_list		*create_polygone(t_point *t0, t_point *t1,
											t_point *t2, int color)
{
	t_fdf_poly_list	*lst;

	lst = (t_fdf_poly_list *)malloc(sizeof(t_fdf_poly_list));
	lst->polygone = (t_fdf_poly *)malloc(sizeof(t_fdf_poly));
	lst->next = NULL;
	point_cpy(&(lst->polygone->p0), t0);
	point_cpy(&(lst->polygone->p1), t1);
	point_cpy(&(lst->polygone->p2), t2);
	lst->polygone->color = color;
	lst->polygone->normal = calc_normal(lst->polygone);
	return (lst);
}

void				add_polygone_to_list(t_fdf_poly_list **list,
											t_fdf_poly_list *new_lst)
{
	t_fdf_poly_list	*ptr;

	ptr = *list;
	if (ptr == NULL)
	{
		*list = new_lst;
		return ;
	}
	while ((ptr)->next != NULL)
		ptr = (ptr)->next;
	ptr->next = new_lst;
	return ;
}

t_point				calc_middle_point(t_point *a, t_point *b,
											t_point *c, t_point *d)
{
	t_point		resl;
	int			zmin;
	int			zmax;

	resl.x = ((c->x - a->x) / 2) + a->x;
	resl.y = ((a->y - b->y) / 2) + b->y;
	zmin = fmin(a->z, fmin(b->z, fmin(c->z, d->z)));
	zmax = fmax(a->z, fmax(b->z, fmax(c->z, d->z)));
	resl.z = (abs(zmax - zmin) / 2) + zmin;
	return (resl);
}

t_fdf_poly_list		*create_list_of_polygones(t_fdf_matrix *mtrx)
{
	t_fdf_list		*lst1;
	t_fdf_list		*lst2;
	t_fdf_matrix	*mtrx_prev;
	t_fdf_matrix	*mtrx_curr;
	t_fdf_poly_list	*list_tmp;
	t_point			middle;

	mtrx_curr = mtrx;
	list_tmp = NULL;
	while (mtrx_curr->next != NULL)
	{
		mtrx_prev = mtrx_curr;
		mtrx_curr = mtrx_curr->next;
		lst1 = mtrx_curr->list;
		lst2 = mtrx_prev->list;
		while (lst1->next && lst2->next)
		{
			middle = calc_middle_point(&lst2->p, &lst1->p,
								&lst2->next->p, &lst1->next->p);
			add_polygone_to_list(&(list_tmp),
			create_polygone(&lst1->p, &lst1->next->p, &middle, WHITE));
			add_polygone_to_list(&(list_tmp),
			create_polygone(&lst1->p, &lst2->p, &middle, WHITE));
			add_polygone_to_list(&(list_tmp),
			create_polygone(&lst2->p, &lst2->next->p, &middle, WHITE));
			add_polygone_to_list(&(list_tmp),
			create_polygone(&lst1->next->p, &lst2->next->p, &middle, WHITE));
			lst1 = lst1->next;
			lst2 = lst2->next;
		}
	}
	return (list_tmp);
}