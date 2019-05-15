/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coolfdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 21:39:19 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/14 19:09:40 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coolfdf.h>

void				ft_exit(int a)
{
	exit(a);
}

void				point_cpy(t_point *to, t_point *from)
{
	to->x = from->x;
	to->y = from->y;
	to->z = from->z;
	to->w = from->w;
	to->color = from->color;
}

t_fdf_poly_list		*create_polygone(t_point *t0, t_point *t1, t_point *t2, int color)
{
	t_fdf_poly_list	*lst;

	lst = (t_fdf_poly_list *)malloc(sizeof(t_fdf_poly_list));
	lst->polygone = (t_fdf_poly *)malloc(sizeof(t_fdf_poly));
	lst->next = NULL;
	point_cpy(&(lst->polygone->p0), t0);
	point_cpy(&(lst->polygone->p1), t1);
	point_cpy(&(lst->polygone->p2), t2);
	lst->polygone->color = color;
	lst->polygone->normal = calc_normal(lst->polygone);
	return (lst);
}

void	add_polygone_to_list(t_fdf_poly_list **list, t_fdf_poly_list *new_lst)
{
	t_fdf_poly_list	*ptr;

	ptr = *list;
	if (ptr == NULL)
	{
		*list = new_lst;
		return ;
	}
	while ((ptr)->next != NULL)
		ptr = (ptr)->next;
	ptr->next = new_lst;
	return ;
}

int				ft_min(int a, int b)
{
	return (a < b ? a : b);
}

int				ft_max(int a, int b)
{
	return (a > b ? a : b);
}

t_point				*calc_middle_point(t_point *a, t_point *b, t_point *c, t_point *d)
{
	t_point		*resl;
	int			zmin;
	int			zmax;

	resl = (t_point *)malloc(sizeof(t_point));
	resl->x = ((c->x - a->x) / 2) + a->x;
	resl->y = ((a->y - b->y) / 2) + b->y;
	zmin = ft_min(a->z, ft_min(b->z ,ft_min(c->z, d->z)));
	zmax = ft_max(a->z, ft_max(b->z ,ft_max(c->z, d->z)));
	resl->z = (ft_abs(zmax - zmin) / 2) + zmin;
	resl->color = WHITE;
	return (resl);
}

t_fdf_poly_list		*create_list_of_polygones(void *mxl_ptr, void *win_ptr, t_fdf_matrix	*mtrx, t_fdf_image *img)
{
	t_fdf_list		*lst1;
	t_fdf_list		*lst2;
	t_fdf_matrix	*mtrx_prev;
	t_fdf_matrix	*mtrx_curr;
	t_fdf_poly_list	*list_tmp;
	t_point			*middle;

	mtrx_curr = mtrx;
	list_tmp = NULL;
	while (mtrx_curr->next != NULL)
	{
		mtrx_prev = mtrx_curr;
		mtrx_curr = mtrx_curr->next;
		lst1 = mtrx_curr->list;
		lst2 = mtrx_prev->list;
		while (lst1->next && lst2->next)
		{
			middle = calc_middle_point(lst2->p, lst1->p, lst2->next->p, lst1->next->p);
			add_polygone_to_list(&(list_tmp), create_polygone(lst1->p, lst1->next->p, middle, WHITE));
			add_polygone_to_list(&(list_tmp), create_polygone(lst1->p, lst2->p, middle, WHITE));
			add_polygone_to_list(&(list_tmp), create_polygone(lst2->p, lst2->next->p, middle, WHITE));
			add_polygone_to_list(&(list_tmp), create_polygone(lst1->next->p, lst2->next->p, middle, WHITE));
			lst1 = lst1->next;
			lst2 = lst2->next;
			free(middle);
		}
	}
	return (list_tmp);
}

void	zbuffer_init(int *zbuffer)
{
	int i;

	i = WIN_HEIGTH * WIN_WIDTH - 1;
	while (i)
	{
		zbuffer[i] = (INT32_MIN);
		i--;
	}
}

void	find_offset_polylist(t_fdf_poly_list *polylist, int *offsetx, int *offsety)
{
	t_fdf_poly_list	*list;
	int				mx;
	int				my;

	list = polylist;
	mx = 0;
	my = 0;
	while (list)
	{
		mx = ft_max(mx, ft_max(list->polygone->p0.x, ft_max(list->polygone->p1.x, list->polygone->p2.x)));
		my = ft_max(my, ft_max(list->polygone->p0.y, ft_max(list->polygone->p1.y, list->polygone->p2.y)));
		list = list->next;
	}
	*offsetx = WIN_WIDTH / 2;
	*offsety = WIN_HEIGTH / 2;
}

void	normalize_and_find_offset_polylist(t_fdf_poly_list *polylist, int *offsetx, int *offsety)
{
	t_fdf_poly_list	*list;
	int				mx;
	int				my;

	list = polylist;
	mx = 0;
	my = 0;
	while (list)
	{
		mx = ft_max(mx, ft_max(list->polygone->p0.x, ft_max(list->polygone->p1.x, list->polygone->p2.x)));
		my = ft_max(my, ft_max(list->polygone->p0.y, ft_max(list->polygone->p1.y, list->polygone->p2.y)));
		list = list->next;
	}
	list = polylist;
	while (list)
	{
		list->polygone->p0.x -= mx / 2;
		list->polygone->p1.x -= mx / 2;
		list->polygone->p2.x -= mx / 2;
		list->polygone->p0.y -= my / 2;
		list->polygone->p1.y -= my / 2;
		list->polygone->p2.y -= my / 2;
		list = list->next;
	}
	*offsetx = WIN_WIDTH / 2;
	*offsety = WIN_HEIGTH / 2;
}

void	draw_land_scapes(void *mxl_ptr, void *win_ptr, t_fdf_matrix	*mtrx, t_fdf_image *img)
{
	t_fdf_window	*win;
	t_fdf_poly_list	*list;
	void			*ptr_image;

	win = (t_fdf_window *)img->window;
	zbuffer_init(img->zbuffer);
	ft_bzero(img->data_image, img->size_line);
	win->polygone_list = create_list_of_polygones(mxl_ptr, win_ptr, mtrx, img);
	normalize_and_find_offset_polylist(win->polygone_list, &(img->offsetx), &(img->offsety));
	handle_draw(img);
	info(win);
	ptr_image = img->ptr_image;
	mlx_put_image_to_window(mxl_ptr, win->win_ptr, ptr_image, 0, 0);
}

int		main(int argc, char **argv)
{
	t_fdf_window	win_main;
	t_fdf_image		image;

	image.zbuffer = (int *)malloc(sizeof(int) * WIN_WIDTH * WIN_HEIGTH);
	if (argc != 2)
		return (0);
	win_main.width = WIN_WIDTH;
	win_main.height = WIN_HEIGTH;
	win_main.mlx = mlx_init();
	image.width = WIN_WIDTH;
	image.height = WIN_HEIGTH;
	win_main.mtrx = fdf_reader(argv[1], &win_main, &image);
	image.ptr_image = mlx_new_image(win_main.mlx, image.width, image.height);
	image.data_image = mlx_get_data_addr(image.ptr_image, &(image.bpp), &(image.size_line), &(image.endian));
	win_main.win_ptr = mlx_new_window(win_main.mlx, win_main.width, win_main.height, "FdF");
	image.window = &win_main;
	win_main.wininfo.lines = 1;
	win_main.wininfo.polygones = 1;
	win_main.anglex = 10;
	win_main.angley = 10;
	win_main.anglez = 10;
	win_main.q = (t_fdf_c_terion){0, 0, 0, 1};
	draw_land_scapes(win_main.mlx, win_main.win_ptr, win_main.mtrx, &image);
	mlx_hook(win_main.win_ptr, 2, 0, rotate_handle, &image);
	mlx_hook(win_main.win_ptr, 3, 0, zoom_handle, &image);
	mlx_loop(win_main.mlx);
}
