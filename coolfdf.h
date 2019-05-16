/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coolfdf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 21:40:51 by zytrams           #+#    #+#             */
/*   Updated: 2019/05/16 16:15:46 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COOLFDF_H
# define COOLFDF_H
# define WHITE 16777215
# define BLACK 0x000000
# define GREEN 0x00FF00
# define RED 0xFF4500
# define WIN_WIDTH 1200
# define WIN_HEIGTH 800
# include <stdlib.h>
# include <stdio.h>
# include "lib/minilibx/mlx.h"
# include <libft.h>
# include <fcntl.h>
# include <math.h>

typedef struct				s_fdf_info
{
	char					lines;
	char					polygones;
}							t_fdf_info;

typedef	struct				s_point
{
	int						x;
	int						y;
	int						z;
	int						w;
	int						color;
}							t_point;

typedef struct				s_fdf_c_vector3
{
	double					x;
	double					y;
	double					z;
}							t_fdf_c_vector3;

typedef struct				s_fdf_poly
{
	t_point					p0;
	t_point					p1;
	t_point					p2;
	t_fdf_c_vector3			*normal;
	int						color;
}							t_fdf_poly;

typedef struct				s_fdf_poly_list
{
	t_fdf_poly				*polygone;
	struct	s_fdf_poly_list	*next;
}							t_fdf_poly_list;

typedef struct				s_fdf_list
{
	t_point					*p;
	struct s_fdf_list		*next;
}							t_fdf_list;

typedef	struct				s_fdf_matrix
{
	t_fdf_list				*list;
	struct s_fdf_matrix		*next;
}							t_fdf_matrix;

typedef struct				s_fdf_mtrx_row
{
	double					a;
	double					b;
	double					c;
	double					d;
}							t_fdf_mtrx_row;


typedef struct				s_fdf_c_matrix4
{
	t_fdf_mtrx_row			r0;
	t_fdf_mtrx_row			r1;
	t_fdf_mtrx_row			r2;
	t_fdf_mtrx_row			r3;
}							t_fdf_c_matrix4;

typedef struct				s_fdf_rot_mtrxs
{
	t_fdf_c_matrix4			*axis_x;
	t_fdf_c_matrix4			*axis_y;
	t_fdf_c_matrix4			*axis_z;
}							t_fdf_rot_mtrxs;

typedef struct				s_fdf_c_terion
{
	double					x;
	double					y;
	double					z;
	double					w;
}							t_fdf_c_terion;


typedef	struct				s_fdf_window
{
	void					*win_ptr;
	int						width;
	int						height;
	int						anglex;
	int						angley;
	int						anglez;
	t_fdf_c_terion			q;
	t_fdf_matrix			*mtrx;
	void					*mlx;
	t_fdf_poly_list			*polygone_list;
	t_fdf_rot_mtrxs			ptrs_to_mtrxs;
	t_fdf_info				wininfo;
}							t_fdf_window;

typedef struct				s_fdf_image
{
	void					*ptr_image;
	char					*data_image;
	int						width;
	int						height;
	t_fdf_window			*window;
	int						endian;
	int						size_line;
	int						bpp;
	int						*zbuffer;
	int						offsetx;
	int						offsety;
	int						offsetz;
	t_point					idle_normal;
}							t_fdf_image;

typedef struct				s_fdf_c_vec2f
{
	int						a;
	int						b;
}							t_fdf_c_vec2f;

void						normalize_points(t_fdf_matrix *mtrx, t_fdf_image *img, int mx, int my);
void						draw_land_scapes(void *mxl_ptr, void *win_ptr, t_fdf_matrix	*mtrx, t_fdf_image *img);
int							ft_abs(int num);
void						put_on_image(int x, int y, int color, t_fdf_image *image);
t_fdf_list					*add_new_point(int x, int y, int z);
void						list_append(t_fdf_list **list, int x, int y, int z);
t_fdf_matrix				*create_line_of_matrix(void);
void						matrix_append(t_fdf_matrix **mtrx, t_fdf_matrix *data);
t_fdf_matrix				*create_matrix_of_dots(int fd, t_fdf_window *win_main, t_fdf_image *img);
t_fdf_matrix				*fdf_reader(char *filename, t_fdf_window *win_main, t_fdf_image *img);
void						paint_lines(void *mxl_ptr, void	*win_ptr, t_fdf_matrix	*mtrx, t_fdf_image *img);
void						ft_exit(int a);
int							rotate_handle(int key, void *param);
void						printf_dots(t_fdf_matrix *mtrx);
int							movement_handle(int key, void *param);
void						move_right(t_fdf_window *window);
void						move_left(t_fdf_window *window);
void						move_top(t_fdf_window *window);
void						move_down(t_fdf_window *window);
void						triangle(t_fdf_poly *t, t_fdf_image *image, int offsetx, int offsety);
void						define_triangle(t_fdf_poly *t, double a0, double a1, double b0, double b1, double c0, double c1, int color);
void						point_swap(t_point *t0, t_point *t1);
t_fdf_poly_list				*create_list_of_polygones(void *mxl_ptr, void *win_ptr, t_fdf_matrix	*mtrx, t_fdf_image *img);
void						add_polygone_to_list(t_fdf_poly_list **list, t_fdf_poly_list *new_lst);
t_fdf_poly_list				*create_polygone(t_point *t0, t_point *t1, t_point *t2, int color);
void						point_cpy(t_point *to, t_point *from);
t_fdf_c_vector3				*cross_vec3(t_fdf_c_vector3 *v1, t_fdf_c_vector3 *v2);
t_fdf_c_vector3				*create_vector(t_point *a, t_point *b);
t_fdf_c_vector3				*calc_normal(t_fdf_poly *poly);
void						normalize_vec3(t_fdf_c_vector3 *normal);
double						magnitude(t_fdf_c_vector3 *normal);
t_fdf_c_matrix4				*create_rot_matrix_x(double angle, int rad);
t_fdf_c_matrix4				*create_rot_matrix_y(double angle, int rad);
t_fdf_c_matrix4				*create_rot_matrix_z(double angle, int rad);
void						matrix_multiply(t_point *a, t_fdf_c_matrix4 *rot_matrix);
void						rotate(t_fdf_image * img, t_fdf_poly_list *list, t_fdf_c_terion q);
int							ft_max(int a, int b);
int							ft_min(int a, int b);
void						zbuffer_init(int *zbuffer);
void						find_offset_polylist(t_fdf_poly_list *polylist, int *offsetx, int *offsety);
void						bresenham_line(t_point *beg, t_point *end, t_fdf_image *image, int color, int offsetx, int offsety);
void						normalize_and_find_offset_polylist(t_fdf_poly_list *polylist, int *offsetx, int *offsety);
void						zoom_in(t_fdf_poly_list *polylist);
void						zoom_out(t_fdf_poly_list *polylist);
void						handle_draw(t_fdf_image * img);
int							zoom_handle(int key, void *param);
void						ft_swap(int  *a, int *b);
t_fdf_c_terion				quaternion_multiply(t_fdf_c_terion first, t_fdf_c_terion second);
t_fdf_c_terion				rotate_around(t_point axis, double angle);
t_point						project_q(t_point *origin, t_fdf_c_terion rot);
double						dot_product(t_fdf_c_vector3 *normal);
void						triangle_lines(t_fdf_poly *t, t_fdf_image *image, double offsetx, double offsety);
void						info(t_fdf_window *window);

#endif
