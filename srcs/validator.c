/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:02:16 by zytrams           #+#    #+#             */
/*   Updated: 2019/06/04 15:22:25 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		validate(t_fdf_matrix *mtrx)
{
	int				fsize;
	t_fdf_matrix	*t_mtrx;

	fsize = get_size(mtrx->list);
	t_mtrx = mtrx;
	while (t_mtrx)
	{
		if (get_size(t_mtrx->list) != fsize)
			return (0);
		t_mtrx = t_mtrx->next;
	}
	return (1);
}

int		get_size(t_fdf_list *list)
{
	int			res;
	t_fdf_list	*t_list;

	res = 0;
	t_list = list;
	while (t_list)
	{
		res++;
		t_list = t_list->next;
	}
	return (res);
}
