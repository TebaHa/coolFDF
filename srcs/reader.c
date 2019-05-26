/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:07:28 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/26 18:56:44 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_fdf_list			*add_new_point(int x, int y, int z)
{
	t_fdf_list *newlst;

	newlst = (t_fdf_list *)malloc(sizeof(t_fdf_list));
	newlst->p.x = x;
	newlst->p.y = y;
	newlst->p.z = z * 30;
	newlst->next = NULL;
	return (newlst);
}

t_fdf_matrix		*create_line_of_matrix(void)
{
	t_fdf_matrix	*mtrx;

	mtrx = (t_fdf_matrix *)malloc(sizeof(t_fdf_matrix));
	mtrx->list = NULL;
	mtrx->next = NULL;
	return (mtrx);
}

void				matrix_append(t_fdf_matrix **mtrx, t_fdf_matrix *data)
{
	t_fdf_matrix	*tmp;

	tmp = *mtrx;
	if (*mtrx == NULL)
	{
		*mtrx = data;
		return ;
	}
	else if (tmp->next == NULL)
	{
		tmp->next = data;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = data;
}

void				list_append(t_fdf_list **list, int x, int y, int z)
{
	t_fdf_list	*ptr;

	ptr = *list;
	if (*list == NULL)
	{
		*list = add_new_point(x, y, z);
		return ;
	}
	while ((ptr)->next != NULL)
		ptr = (ptr)->next;
	ptr->next = add_new_point(x, y, z);
	return ;
}

void				create_matrix_of_dots(int fd, t_fdf_matrix **mtrx)
{
	t_fdf_matrix	*tmp;
	char			**dots;
	char			*line;
	int				i;
	int				y;

	y = 0;
	*mtrx = NULL;
	while (get_next_line(fd, &line))
	{
		tmp = create_line_of_matrix();
		dots = ft_strsplit(line, ' ');
		i = 0;
		while (dots[i] != NULL)
		{
			list_append(&(tmp->list), (i * 10), y, atoi(dots[i]));
			i++;
		}
		i = -1;
		while (dots[++i] != NULL)
			free(dots[i]);
		y += 10;
		matrix_append(mtrx, tmp);
	}
}
