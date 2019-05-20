/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 21:40:38 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/18 17:07:49 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

t_fdf_list	*add_new_point(int x, int y, int z)
{
	t_fdf_list *newlst;

	newlst = (t_fdf_list *)malloc(sizeof(t_fdf_list));
	newlst->p = (t_point *)malloc(sizeof(t_point));
	newlst->p->x = x;
	newlst->p->y = y;
	newlst->p->z = z * 10;
	newlst->p->w = 1;
	newlst->p->color = GREEN;
	newlst->next = NULL;
	return (newlst);
}

void	list_append(t_fdf_list **list, int x, int y, int z)
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

t_fdf_matrix	*create_line_of_matrix(void)
{
	t_fdf_matrix	*mtrx;

	mtrx = (t_fdf_matrix *)malloc(sizeof(t_fdf_matrix));
	mtrx->list = NULL;
	mtrx->next = NULL;
	return (mtrx);
}

void	matrix_append(t_fdf_matrix **mtrx, t_fdf_matrix *data)
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
	return ;
}

void	normalize_points(t_fdf_matrix *mtrx, t_fdf_image *img, int mx, int my)
{
	t_fdf_matrix	*t_mtrx;
	t_fdf_list		*t_list;
	int				offsetx;
	int				offsety;

	t_mtrx = mtrx;
	offsetx = (img->width - mx) / 2;
	offsety = (img->height - my) / 2;
	while(t_mtrx)
	{
		t_list = t_mtrx->list;
		while (t_list)
		{
			t_list->p->x += offsetx;
			t_list->p->y += offsety;
			t_list = t_list->next;
		}
		t_mtrx = t_mtrx->next;
	}
}

t_fdf_matrix	*create_matrix_of_dots(int fd, t_fdf_window *win_main, t_fdf_image *img)
{
	t_fdf_matrix	*mtrx;
	t_fdf_matrix	*tmp;
	char			**dots;
	char			*line;
	int				i;
	int				y;

	y = 0;
	mtrx = NULL;
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
		i = 0;
		while(dots[i])
		{
			free(dots[i]);
			i++;
		}
		y += 10;
		matrix_append(&mtrx, tmp);
	}
	img->width = 1200;
	img->height = 800;
	return (mtrx);
}

t_fdf_matrix	*fdf_reader(char *filename, t_fdf_window *win_main, t_fdf_image *img)
{
	int				fd;
	t_fdf_matrix	*mtrx;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_exit(-1);
	mtrx = create_matrix_of_dots(fd, win_main, img);
	if (close(fd) < 0)
		ft_exit(1);
	return (mtrx);
}
