/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:34:34 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/16 18:42:22 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

void	info(t_fdf_window *window)
{
	void	*t_mlx;
	void	*t_win_ptr;

	t_mlx = window->mlx;
	t_win_ptr = window->win_ptr;
	if (window->wininfo.lines == 1)
		mlx_string_put(t_mlx, t_win_ptr, 10, 10, WHITE, "lines");
	else
		mlx_string_put(t_mlx, t_win_ptr, 10, 10, RED, "lines");
	if (window->wininfo.polygones == 1)
		mlx_string_put(t_mlx, t_win_ptr, 10, 30, WHITE, "polygones");
	else
		mlx_string_put(t_mlx, t_win_ptr, 10, 30, RED, "polygones");
}
