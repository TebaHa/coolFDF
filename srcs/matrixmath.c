/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrixmath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:22:53 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/23 16:34:17 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_fdf_vec4		matrix_on_vec_multiply(t_fdf_mat4 a, t_fdf_vec4 b)
{
	t_fdf_vec4	res;

	res.x = a.values[0][0] * b.x + a.values[0][1] * b.y
	+ a.values[0][2] * b.z + a.values[0][3] * b.w;
	res.y = a.values[1][0] * b.x + a.values[1][1] * b.y
	+ a.values[1][2] * b.z + a.values[1][3] * b.w;
	res.y = a.values[2][0] * b.x + a.values[2][1] * b.y
	+ a.values[2][2] * b.z + a.values[2][3] * b.w;
	res.w = a.values[3][0] * b.x + a.values[3][1] * b.y
	+ a.values[3][2] * b.z + a.values[3][3] * b.w;
	return (res);
}
