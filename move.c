/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 06:09:00 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/09 06:09:19 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>
#include <key_macroses.h>

void	move_left(t_fdf_window *window)
{
	t_fdf_matrix	*mtrx;
	t_fdf_list		*list;
	double			x;
	double			y;
	double			z;

	mtrx = window->mtrx;
	while (mtrx)
	{
		list = mtrx->list;
		while (list)
		{
			list->p->x -= 25;
			list = list->next;
		}
		mtrx = mtrx->next;
	}
}

void	move_down(t_fdf_window *window)
{
	t_fdf_matrix	*mtrx;
	t_fdf_list		*list;
	double			x;
	double			y;
	double			z;

	mtrx = window->mtrx;
	while (mtrx)
	{
		list = mtrx->list;
		while (list)
		{
			list->p->y += 25;
			list = list->next;
		}
		mtrx = mtrx->next;
	}
}

void	move_top(t_fdf_window *window)
{
	t_fdf_matrix	*mtrx;
	t_fdf_list		*list;
	double			x;
	double			y;
	double			z;

	mtrx = window->mtrx;
	while (mtrx)
	{
		list = mtrx->list;
		while (list)
		{
			list->p->y -= 25;
			list = list->next;
		}
		mtrx = mtrx->next;
	}
}

void	move_right(t_fdf_window *window)
{
	t_fdf_matrix	*mtrx;
	t_fdf_list		*list;
	double			x;
	double			y;
	double			z;

	mtrx = window->mtrx;
	while (mtrx)
	{
		list = mtrx->list;
		while (list)
		{
			list->p->x += 25;
			list = list->next;
		}
		mtrx = mtrx->next;
	}
}
