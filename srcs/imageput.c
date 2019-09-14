/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imageput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:14:07 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/04 00:16:55 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	ft_swap(int *a, int *b)
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
	t0->x = t1->x;
	t0->y = t1->y;
	t0->z = t1->z;
	t1->x = tmp.x;
	t1->y = tmp.y;
	t1->z = tmp.z;
}

void	put_on_image(int x, int y, int color, t_fdf_image *image)
{
	size_t	offset;
	int		*ptr;

	ptr = (int *)image->ptr_data;
	offset = x + image->ptr_fdf_window->width * y;
	ptr[offset] = color;
}
