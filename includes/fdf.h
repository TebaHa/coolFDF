/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 13:38:41 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/27 05:07:47 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COOLFDF_H
# define COOLFDF_H
# define WHITE 16777215
# define BLACK 0x000000
# define GREEN 0x00FF00
# define RED 0xFF4500
# define WIN_WIDTH 2400
# define WIN_HEIGTH 1200
# define PERSPECTIVE 1600
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>
# include <math.h>
# include <macroses.h>

typedef enum				e_bool
{
	FALSE,
	TRUE
}							t_bool;

typedef enum				e_tpos
{
	LEFT,
	RIGHT
}							t_tpos;

typedef struct				s_fdf_vec4
{
	float					x;
	float					y;
	float					z;
	float					w;
}							t_fdf_vec4;

typedef struct				s_fdf_vec3
{
	float					x;
	float					y;
	float					z;
}							t_fdf_vec3;

typedef struct				s_fdf_mat4
{
	float					values[4][4];
}							t_fdf_mat4;

typedef	struct				s_point
{
	int						x;
	int						y;
	int						z;
}							t_point;

typedef struct				s_fdf_qterion
{
	float					x;
	float					y;
	float					z;
	float					w;
}							t_fdf_qternion;

typedef struct				s_fdf_list
{
	t_point					p;
	struct s_fdf_list		*next;
}							t_fdf_list;

typedef	struct				s_fdf_matrix
{
	t_fdf_list				*list;
	struct s_fdf_matrix		*next;
}							t_fdf_matrix;

typedef struct				s_fdf_poly
{
	t_point					p0;
	t_point					p1;
	t_point					p2;
	t_fdf_vec3				normal;
	int						color;
	t_tpos					pos_status;
}							t_fdf_poly;

typedef struct				s_fdf_poly_list
{
	t_fdf_poly				*polygone;
	struct s_fdf_poly_list	*next;
}							t_fdf_poly_list;

typedef struct				s_fdf_info_block
{
	char					lines;
	char					polygones;
	char					perspective;
}							t_fdf_info_block;

typedef struct				s_fdf_window
{
	void					*ptr_win;
	void					*mlx;
	int						width;
	int						height;
	t_fdf_info_block		info;
	t_fdf_matrix			*mtrx_data;
}							t_fdf_window;

typedef struct				s_fdf_image
{
	t_fdf_window			*ptr_fdf_window;
	void					*ptr_img;
	char					*ptr_data;
	int						*zbuffer;
	int						endian;
	int						size_line;
	int						bpp;
	int						offsetx;
	int						offsety;
	float					scalex;
	float					scaley;
	float					scalez;
	int						anglex;
	int						angley;
	int						anglez;
	t_fdf_qternion			qtr;
	t_fdf_poly_list			*polygones;
}							t_fdf_image;

typedef struct				s_bcontex
{
	int						steep;
	float					dx;
	float					dy;
	int						error2;
	int						derror2;
	int						x;
	int						y;
	t_point					b;
	t_point					e;
}							t_bcontex;

typedef struct				s_triangle
{
	int						total_height;
	int						second_half;
	int						i;
	int						j;
	int						segment_height;
	t_point					a;
	t_point					b;
	t_point					t0;
	t_point					t1;
	t_point					t2;
	float					alpha;
	float					beta;
	float					intensity;
	float					phi;
	t_point					p;
	int						offsetx;
	int						offsety;
}							t_triangle;

/*
** INITILIZE
*/
void						window_initilize(t_fdf_window *win, char *filename);
void						image_initilize(t_fdf_image *img);

/*
** READER
*/
t_fdf_list					*add_new_point(int x, int y, int z);
t_fdf_matrix				*create_line_of_matrix(void);
void						matrix_append(t_fdf_matrix **mtrx,
								t_fdf_matrix *data);
void						list_append(t_fdf_list **list, int x, int y, int z);
void						create_matrix_of_dots(int fd, t_fdf_matrix **mtrx);
t_fdf_matrix				*fdf_reader(char *filename);

/*
** ZBUFFER
*/
void						zbuffer_init(int *zbuffer);

/*
** POLYGONIZER
*/
t_fdf_poly_list				*create_list_of_polygones(t_fdf_matrix *mtrx,
								int color);
t_point						calc_middle_point(t_point *a, t_point *b,
								t_point *c, t_point *d);
void						add_polygone_to_list(t_fdf_poly_list
								**list, t_fdf_poly_list *new_lst);
t_fdf_poly_list				*create_polygone(t_point *dots[3],
							t_tpos pstatus, int color);
void						point_cpy(t_point *to, t_point *from);

/*
** ZOOM
*/
void						zoom_in(float *scalex,
								float *scaley, float *scalez);
void						zoom_out(float *scalex,
								float *scaley, float *scalez);

/*
** HANDLERS
*/
void						handle_draw(t_fdf_image *img);
int							zoom_handle(int key, void *param);
int							rotate_handle(int key, void *param);

/*
** RASTERIZER
*/
void						triangle(t_fdf_poly *t, t_fdf_image *image);
int							init_triangle(t_fdf_poly *t, t_triangle *trg);
void						do_draw(t_triangle *trg,
								t_fdf_image *image, int color);
void						do_calc(t_triangle *trg);

/*
** BRESENHAM
*/
void						triangle_lines(t_fdf_poly *t,
								t_fdf_image *image);
void						bresenham_line(t_point *beg,
								t_point *end, t_fdf_image *image, int color);

/*
** QUATERION
*/
t_fdf_qternion				quaternion_multiply(t_fdf_qternion first,
							t_fdf_qternion second);
t_fdf_qternion				rotate_around(t_point axis, float angle);
t_point						calc_point(t_point *origin,
							t_fdf_qternion rot, float scales[3]);

/*
** JUNK
*/
void						ft_swap(int *a, int *b);
void						point_swap(t_point *t0, t_point *t1);
void						put_on_image(int x, int y,
								int color, t_fdf_image *image);
void						recount(t_fdf_poly_list *p_list,
								int mx, int my, int mz);
void						add_polygones(t_fdf_list *lst1, t_fdf_list *lst2,
								t_fdf_poly_list **lstp, int color);
void						free_fields(char **options);

/*
** ROTATE
*/
void						rotate(t_fdf_image *img,
								t_fdf_poly_list *list, t_fdf_qternion q);

/*
** NORMAL
*/
t_fdf_vec3					calc_normal(t_fdf_poly *poly);
void						normalize_vec3(t_fdf_vec3 *normal);
float						magnitude(t_fdf_vec3 *normal);
t_fdf_vec3					create_vector(t_point *a, t_point *b);
t_fdf_vec3					cross_vec3(t_fdf_vec3 v1, t_fdf_vec3 v2);

/*
** EXIT
*/
void						ft_exit(int a);

t_fdf_mat4					getzeroaffinmat4(void);
t_fdf_vec4					matrix_on_vec_multiply(t_fdf_mat4 a, t_fdf_vec4 b);

/*
** COLORIZER
*/
float						percent(int start, int end, int current);
int							get_light(int start, int end, float percentage);
int							get_color(int current, int start,
								int end, int colors[2]);

int							print_check(t_fdf_poly polygon);
void						draw(t_fdf_poly plg, t_fdf_image *img);
void						put_info(t_fdf_image *img);

/*
** VALIDATOR
*/
int							validate(t_fdf_matrix *mtrx);
int							get_size(t_fdf_list *list);

#endif
