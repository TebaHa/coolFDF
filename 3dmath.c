/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3dmath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 06:35:00 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/15 15:48:02 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

int						ft_sqrt(int num)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (num == 0 || num == 1)
		return (num);
	while (res <= num)
	{
		i++;
		res = i * i;
	}
	return (i - 1);
}

t_fdf_c_vector3			*cross_vec3(t_fdf_c_vector3 *v1, t_fdf_c_vector3 *v2)
{
	t_fdf_c_vector3	*v3normal;

	v3normal = (t_fdf_c_vector3 *)malloc(sizeof(t_fdf_c_vector3));
	v3normal->x = (v1->y * v2->z) - (v1->z * v2->y);
	v3normal->y = (v1->z * v2->x) - (v1->x * v2->z);
	v3normal->z = (v1->x * v2->y) - (v1->y * v2->x);

	return (v3normal);
}

t_fdf_c_vector3			*create_vector(t_point *a, t_point *b)
{
	t_fdf_c_vector3 *vec3;

	vec3 = (t_fdf_c_vector3 *)malloc(sizeof(t_fdf_c_vector3));
	vec3->x = a->x - b->x;
	vec3->y = a->y - b->y;
	vec3->z = a->z - b->z;

	return (vec3);
}

double					magnitude(t_fdf_c_vector3 *normal)
{
	return (double)ft_sqrt((normal->x * normal->x) +
	(normal->y * normal->y) + (normal->z * normal->z));
}

void					normalize_vec3(t_fdf_c_vector3 *normal)
{
	double	magn;

	magn = magnitude(normal);
	normal->x /= magn;
	normal->y /= magn;
	normal->z /= magn;
}

t_fdf_c_vector3			*calc_normal(t_fdf_poly *poly)
{
	t_fdf_c_vector3		*vec1;
	t_fdf_c_vector3		*vec2;
	t_fdf_c_vector3		*normal;
	t_point		t0;
	t_point		t1;
	t_point		t2;

	t0 = (t_point){poly->p0.x, poly->p0.y, poly->p0.z, 0, 0};
	t1 = (t_point){poly->p1.x, poly->p1.y, poly->p1.z, 0, 0};
	t2 = (t_point){poly->p2.x, poly->p2.y, poly->p2.z, 0, 0};
	if (t0.x > t1.x)
		point_swap(&(t0), &(t1));
	if (t0.x > t2.x)
		point_swap(&(t0), &(t2));
	if (t1.y > t2.y)
		point_swap(&(t1), &(t2));
	vec1 = create_vector(&(t0), &(t2));
	vec2 = create_vector(&(t0), &(t1));
	normal = cross_vec3(vec1, vec2);
	normalize_vec3(normal);
	free(vec1);
	free(vec2);
	return (normal);
}
