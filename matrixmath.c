/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixmath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 08:26:17 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/14 18:04:01 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

double				get_rad(double angle)
{
	return (angle * 3.14 / 180.0);
}
/*
t_fdf_c_matrix4		*create_rot_matrix_x(double angle, int rad)
{
	t_fdf_c_matrix4 *matrix;

	if (rad == 0)
		angle = get_rad(angle);
	matrix = (t_fdf_c_matrix4 *)malloc(sizeof(t_fdf_c_matrix4));
	matrix->r0.a = 1;
	matrix->r1.a = 0;
	matrix->r2.a = 0;
	matrix->r3.a = 0;
	matrix->r0.b = 0;
	matrix->r1.b = cos(angle);
	matrix->r2.b = -sin(angle);
	matrix->r3.b = 0;
	matrix->r0.c = 0;
	matrix->r1.c = sin(angle);
	matrix->r2.c = cos(angle);
	matrix->r3.c = 0;
	matrix->r0.d = 0;
	matrix->r1.d = 0;
	matrix->r2.d = 0;
	matrix->r3.d = 1;
	return (matrix);
}

t_fdf_c_matrix4		*create_rot_matrix_y(double angle, int rad)
{
	t_fdf_c_matrix4 *matrix;

	if (rad == 0)
		angle = get_rad(angle);
	matrix = (t_fdf_c_matrix4 *)malloc(sizeof(t_fdf_c_matrix4));
	matrix->r0.a = cos(angle);
	matrix->r1.a = 0;
	matrix->r2.a = sin(angle);
	matrix->r3.a = 0;
	matrix->r0.b = 0;
	matrix->r1.b = 1;
	matrix->r2.b = 0;
	matrix->r3.b = 0;
	matrix->r0.c = -sin(angle);
	matrix->r1.c = 0;
	matrix->r2.c = cos(angle);
	matrix->r3.c = 0;
	matrix->r0.d = 0;
	matrix->r1.d = 0;
	matrix->r2.d = 0;
	matrix->r3.d = 1;
	return (matrix);
}

t_fdf_c_matrix4		*create_rot_matrix_z(double angle, int rad)
{
	t_fdf_c_matrix4 *matrix;

	if (rad == 0)
		angle = get_rad(angle);
	matrix = (t_fdf_c_matrix4 *)malloc(sizeof(t_fdf_c_matrix4));
	matrix->r0.a = cos(angle);
	matrix->r1.a = -sin(angle);
	matrix->r2.a = 0;
	matrix->r3.a = 0;
	matrix->r0.b = sin(angle);
	matrix->r1.b = cos(angle);
	matrix->r2.b = 0;
	matrix->r3.b = 0;
	matrix->r0.c = 0;
	matrix->r1.c = 0;
	matrix->r2.c = 1;
	matrix->r3.c = 0;
	matrix->r0.d = 0;
	matrix->r1.d = 0;
	matrix->r2.d = 0;
	matrix->r3.d = 1;
	return (matrix);
}

void				matrix_multiply(t_point *a, t_fdf_c_matrix4 *rot_matrix)
{
	a->x = (int)((double)(((double)a->x) * rot_matrix->r0.a) + (double)(((double)a->y) * rot_matrix->r1.a) + (double)(((double)a->z) * rot_matrix->r2.a) + (double)(((double)a->w) * rot_matrix->r3.a));
	a->y = (int)((double)(((double)a->x) * rot_matrix->r0.b) + (double)(((double)a->y) * rot_matrix->r1.b) + (double)(((double)a->z) * rot_matrix->r2.b) + (double)(((double)a->w) * rot_matrix->r3.b));
	a->z = (int)((double)(((double)a->x) * rot_matrix->r0.c) + (double)(((double)a->y) * rot_matrix->r1.c) + (double)(((double)a->z) * rot_matrix->r2.c) + (double)(((double)a->w) * rot_matrix->r3.c));
	a->w = (int)((double)(((double)a->x) * rot_matrix->r0.d) + (double)(((double)a->y) * rot_matrix->r1.d) + (double)(((double)a->z) * rot_matrix->r2.d) + (double)(((double)a->w) * rot_matrix->r3.d));
}
*/
t_fdf_c_terion	quaternion_multiply(t_fdf_c_terion first, t_fdf_c_terion second)
{
	t_fdf_c_terion	res;

	res.w = first.w * second.w - first.x * second.x - first.y * second.y - first.z * second.z;
	res.x = first.w * second.x + first.x * second.w + first.y * second.z - first.z * second.y;
	res.y = first.w * second.y - first.x * second.z + first.y * second.w + first.z * second.x;
	res.z = first.w * second.z + first.x * second.y - first.y * second.x + first.z * second.w;
	return (res);
}

t_fdf_c_terion	rotate_around(t_point axis, double angle)
{
	t_fdf_c_terion	res;

	angle = angle * 3.14 / 180.0;
	res.w = cos(angle / 2);
	res.x = ((double)axis.x) * sin(angle / 2);
	res.y = ((double)axis.y) * sin(angle / 2);
	res.z = ((double)axis.z) * sin(angle / 2);
	return (res);
}

t_point			project_q(t_point *origin, t_fdf_c_terion rot)
{
	t_point a;

	a.x = (1 - 2 * pow(rot.y, 2) - 2 * pow(rot.z, 2)) * origin->x + (2 * rot.x * rot.y - 2 * rot.w * rot.z) * origin->y + (2 * rot.x * rot.z + 2 * rot.w * rot.y) * origin->z;
	a.y = (2 * rot.x * rot.y + 2 * rot.w * rot.z) * origin->x + (1 - 2 * pow(rot.x, 2) - 2 * pow(rot.z, 2)) * origin->y + (2 * rot.y * rot.z - 2 * rot.w * rot.x) * origin->z;
	a.z = (2 * rot.x * rot.z - 2 * rot.w * rot.y) * origin->x + (2 * rot.y * rot.z + 2 * rot.w * rot.x) * origin->y + (1 - 2 * pow(rot.x, 2) - 2 * pow(rot.y, 2)) * origin->z;
	a.x += WIN_WIDTH / 2;
	a.y += WIN_HEIGTH / 2;
	return (a);
}
