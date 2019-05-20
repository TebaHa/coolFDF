/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:32:04 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/20 20:52:34 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_fdf_vec3		cross_vec3(t_fdf_vec3 v1, t_fdf_vec3 v2)
{
	t_fdf_vec3	v3normal;

	v3normal.x = (v1.y * v2.z) - (v1.z * v2.y);
	v3normal.y = (v1.z * v2.x) - (v1.x * v2.z);
	v3normal.z = (v1.x * v2.y) - (v1.y * v2.x);

	return (v3normal);
}

t_fdf_vec3		create_vector(t_point *a, t_point *b)
{
	t_fdf_vec3 vec3;

	vec3.x = a->x - b->x;
	vec3.y = a->y - b->y;
	vec3.z = a->z - b->z;

	return (vec3);
}

double			magnitude(t_fdf_vec3 *normal)
{
	return (sqrt((normal->x * normal->x) +
	(normal->y * normal->y) + (normal->z * normal->z)));
}

void			normalize_vec3(t_fdf_vec3 *normal)
{
	double	magn;

	magn = magnitude(normal);
	normal->x /= magn;
	normal->y /= magn;
	normal->z /= magn;
}

t_fdf_vec3		calc_normal(t_fdf_poly *poly)
{
	t_fdf_vec3		vec1;
	t_fdf_vec3		vec2;
	t_fdf_vec3		normal;
	t_point			t[3];

	t[0] = (t_point){poly->p0.x, poly->p0.y, poly->p0.z};
	t[1] = (t_point){poly->p1.x, poly->p1.y, poly->p1.z};
	t[2] = (t_point){poly->p2.x, poly->p2.y, poly->p2.z};
	vec1 = create_vector(&(t[0]), &(t[2]));
	vec2 = create_vector(&(t[1]), &(t[2]));
	normal = cross_vec3(vec1, vec2);
	normalize_vec3(&normal);
	if (normal.y < 0)
		normal.y = -normal.y;
	if (normal.x < 0)
		normal.x = -normal.x;
	if (normal.z < 0)
		normal.z = -normal.z;
	return (normal);
}
