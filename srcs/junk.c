/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   junk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 21:49:18 by zytrams           #+#    #+#             */
/*   Updated: 2019/06/06 16:56:56 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_fdf_matrix	*fdf_reader(char *filename)
{
	int				fd;
	t_fdf_matrix	*mtrx;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_exit(-1);
	create_matrix_of_dots(fd, &mtrx);
	if (close(fd) < 0)
		ft_exit(1);
	return (mtrx);
}

void			recount(t_fdf_poly_list *p_list, int mx, int my, int mz)
{
	p_list->polygone->p0.x -= mx / 2;
	p_list->polygone->p1.x -= mx / 2;
	p_list->polygone->p2.x -= mx / 2;
	p_list->polygone->p0.y -= my / 2;
	p_list->polygone->p1.y -= my / 2;
	p_list->polygone->p2.y -= my / 2;
	p_list->polygone->p0.z -= mz / 2;
	p_list->polygone->p1.z -= mz / 2;
	p_list->polygone->p2.z -= mz / 2;
}

void			add_polygones(t_fdf_list *lst1, t_fdf_list *lst2,
										t_fdf_poly_list **lstp, int color)
{
	t_point		middle;

	middle = calc_middle_point(&lst2->p, &lst1->p,
								&lst2->next->p, &lst1->next->p);
	add_polygone_to_list(lstp,
	create_polygone(&lst1->p, &lst1->next->p, &middle, color));
	add_polygone_to_list(lstp,
	create_polygone(&lst1->p, &lst2->p, &middle, color));
	add_polygone_to_list(lstp,
	create_polygone(&lst2->p, &lst2->next->p, &middle, color));
	add_polygone_to_list(lstp,
	create_polygone(&lst1->next->p, &lst2->next->p, &middle, color));
}

void			free_fields(char **str_2d)
{
	int		i;

	i = 0;
	while (str_2d && str_2d[i])
	{
		free(str_2d[i]);
		str_2d[i] = NULL;
		i++;
	}
	if (str_2d)
	{
		free(str_2d);
		str_2d = NULL;
	}
}
