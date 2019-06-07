/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:30:25 by zytrams           #+#    #+#             */
/*   Updated: 2019/06/06 16:57:53 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void				zoom_in(double *scalex, double *scaley, double *scalez)
{
	if (*scalex < 4 && *scaley < 4 && *scalez < 4)
	{
		*scalex *= 2;
		*scaley *= 2;
		*scalez *= 2;
	}
}

void				zoom_out(double *scalex, double *scaley, double *scalez)
{
	*scalex /= 2;
	*scaley /= 2;
	*scalez /= 2;
}
