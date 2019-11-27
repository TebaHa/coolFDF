/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:30:25 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/27 05:01:32 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void				zoom_in(float *scalex, float *scaley, float *scalez)
{
	if (*scalex < 4 && *scaley < 4 && *scalez < 4)
	{
		*scalex *= 2;
		*scaley *= 2;
		*scalez *= 2;
	}
}

void				zoom_out(float *scalex, float *scaley, float *scalez)
{
	*scalex /= 2;
	*scaley /= 2;
	*scalez /= 2;
}
