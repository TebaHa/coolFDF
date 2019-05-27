/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternionmagic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:15:52 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/27 08:28:15 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_fdf_qternion	quaternion_multiply(t_fdf_qternion first, t_fdf_qternion second)
{
	t_fdf_qternion	res;

	res.w = first.w * second.w - first.x * second.x
	- first.y * second.y - first.z * second.z;
	res.x = first.w * second.x + first.x * second.w
	+ first.y * second.z - first.z * second.y;
	res.y = first.w * second.y - first.x * second.z
	+ first.y * second.w + first.z * second.x;
	res.z = first.w * second.z + first.x * second.y
	- first.y * second.x + first.z * second.w;
	return (res);
}

t_fdf_qternion	rotate_around(t_point axis, double angle)
{
	t_fdf_qternion	res;

	angle = angle * M_PI / 180.0;
	res.w = cos(angle / 2);
	res.x = ((double)axis.x) * sin(angle / 2);
	res.y = ((double)axis.y) * sin(angle / 2);
	res.z = ((double)axis.z) * sin(angle / 2);
	return (res);
}

t_point			project_q(t_point *origin, t_fdf_qternion rot, double scales[3])
{
	t_point a;
	t_point	org;

	org.x = origin->x * scales[0] * 2;
	org.y = origin->y * scales[1] * 2;
	org.z = origin->z * scales[2] * 2;
	a.x = (1 - 2 * pow(rot.y, 2) - 2.0 * pow(rot.z, 2)) * org.x
	+ (2 * rot.x * rot.y - 2 * rot.w * rot.z) * org.y
	+ (2 * rot.x * rot.z + 2 * rot.w * rot.y) * org.z;
	a.y = (2 * rot.x * rot.y + 2 * rot.w * rot.z) * org.x
	+ (1 - 2 * pow(rot.x, 2) - 2 * pow(rot.z, 2)) * org.y
	+ (2 * rot.y * rot.z - 2 * rot.w * rot.x) * org.z;
	a.z = (2 * rot.x * rot.z - 2 * rot.w * rot.y) * org.x
	+ (2 * rot.y * rot.z + 2 * rot.w * rot.x) * org.y
	+ (1 - 2 * pow(rot.x, 2) - 2 * pow(rot.y, 2)) * org.z;
	return (a);
}
