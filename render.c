/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:58:20 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/15 17:58:35 by zytrams          ###   ########.fr       */
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

void	put_on_image(int x, int y, int color, t_fdf_image *image)
{
	size_t	offset;

	offset = x * 4 + 4 * image->width * y;
	(image->data_image)[offset] = (char)(color);
	(image->data_image)[offset + 1] = (char)(color >> 8);
	(image->data_image)[offset + 2] = (char)(color >> 16);
	(image->data_image)[offset + 3] = (char)(color >> 24);
}
