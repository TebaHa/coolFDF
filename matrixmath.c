/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixmath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 08:26:17 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/15 16:08:35 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

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
