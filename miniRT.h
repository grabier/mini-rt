/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:23 by gmontoro          #+#    #+#             */
/*   Updated: 2025/08/07 17:21:49 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include "libft/libft.h"
#include "MLX42/include/MLX42/MLX42.h"
# define MAX_W 1600  //3840
# define MAX_H 1200  //2160
# define MAX_D 40
# define PI 3.14159

#pragma once

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}			t_color;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_hit
{
	t_vec	colission;
	t_vec	normal;
	t_color	pixel_color;
	int		object;//0 for sph, 1 for planes, 2 for cylinders
	struct s_hit *next;
}			t_hit;

typedef struct s_ray
{
	t_vec	or;
	t_vec	dir;
}			t_ray;

typedef struct s_sph
{
	t_vec			point;
	double			diam;
	t_color			color;
	t_color			pixel_color;
	int				is_colission;
	t_vec			colission;
	int				in;
	struct s_sph	*next;
}			t_sph;

typedef struct s_pl
{
	t_vec			point;
	t_vec			n_vector;
	t_vec			colission;
	t_color			color;
	t_color			pixel_color;
	struct s_pl		*next;
}			t_pl;

typedef struct s_cy
{
	t_vec			point;
	t_vec			colission;
	t_vec			n_vector;
	double			r;
	int				mcol;//colission mode: 0 for lateral, 1 for base, 2 for top
	double			height;
	t_color			color;
	struct s_cy		*next;
}			t_cy;

typedef struct s_cam
{
	t_vec			origin;
	t_vec			fw;//forward
	t_vec			up;
	t_vec			right;
	t_vec			center;
	t_vec			ver;
	t_vec			hor;
	t_vec			ll;//lower left corner of the viewport
	double			fov;
	double			as_ratio;
	double			vp_h;
	double			vp_w;
}			t_cam;

typedef struct collision {
	double depth;
	// informacion sobre el material.
} t_collision;

//as of now, used for passing params to cylinder node creation
typedef struct s_aux
{
	t_vec			point;
	t_vec			n_vector;
	double			diam;
	double			height;
	t_color			color;
}			t_aux;

typedef struct s_parse
{
	mlx_t	*data;
	mlx_image_t	*img;
	struct timeval start;
	int		A;
	double	am_ratio;
	t_color	am_color;
	int		C;
	t_cam	*cam;
	int		L;
	t_vec	l_point;
	double	l_bright;
	t_color	l_color;
	//for the objects, we need lists(can be more than one)
	t_hit	*hit;
	int		sp_count;
	t_sph	*sp;
	int		pl_count;
	t_pl	*pl;
	int		cy_count;
	t_cy	*cy;
	t_color	cy_color;
}			t_parse;

//ft_atod.c
double	ft_atod(char *str);


//gnl.c
char	*get_next_line(int fd);


//utils1.c
void	printv(t_vec v);
void	ft_printcolor(t_color c);
void	ft_debug_parsing(t_parse *p);
void	start_timer(struct timeval *start);
void	end_timer(struct timeval start);


//ambient_parsing.c
int		ft_parse_ambient(char **spline, t_parse *program);
int		ft_init_t_color_am(t_parse *program, int r, int g, int b);


//camera_parsing.c
int		ft_parse_camera(char **sp, t_parse *program);
int		ft_init_cam_origin(t_parse *program, double x, double y, double z);
int		ft_init_cam_dir(t_parse *program, double x, double y, double z);
int		ft_init_cam_fov(t_parse *program, int fov);
void	ft_init_viewport(t_parse *p);


//light parsing.c
int		ft_parse_light(char **sp, t_parse *program);
int		ft_init_t_vec_li(t_parse *program, double x, double y, double z);
int		ft_init_t_color_li(t_parse *program, int r, int g, int b);


//parsing.c
int		ft_parse_line(char *line, t_parse *program);
char	*ft_format_line(char *str);
t_parse	*ft_read_file(int fd);
int		ft_check_extension(char *file);
//t_parse	*ft_free_parsing(t_parse *p);
int		ft_check_parsing (t_parse *p);
t_parse	*ft_parsing(int argc, char **argv);


//parsing_utils.c
int	ft_arg_count(char *str);
int	ft_space_count(char *str);
char	*ft_delete_spaces(char *str, char *dst);
int	ft_check_arg_count(char *str, int arg_count);
int	ft_check_argument(char *str);


//init.c
t_vec ft_init_vec(double x, double y, double z);
t_color ft_init_color(char **sp);
t_parse *ft_init_parse();


//free.c
void	ft_free(char **sp);
t_parse	*ft_free_parsing(t_parse *p);


//sphere_lst.c
void	ft_sphadd_back(t_sph **lst, t_sph *new);
void	ft_sphadd_front(t_sph **lst, t_sph *new);
t_sph	*ft_sphnew(t_vec p, double d, t_color c);
int		ft_sphsize(t_sph *lst);
void	ft_free_sp(t_parse *p);


//sphere_parsing.c
int	ft_parse_sphere(char **sp, t_parse *p);
int	ft_check_color(char **sp);
//t_color ft_init_color(char **sp);
//t_vec ft_init_vec(double x, double y, double z);
int	ft_check_point(double x, double y, double z);
int	ft_init_t_color_sp(t_parse *p, int r, int g, int b);


//plane_lst.c
void	ft_free_pl(t_parse *p);
void	ft_pladd_back(t_pl **lst, t_pl *new);
void	ft_pladd_front(t_pl **lst, t_pl *new);
t_pl	*ft_plnew(t_vec p, t_vec n, t_color c);
int		ft_plsize(t_pl *lst);


//plane_parsing.c
int		ft_parse_plane(char **sp, t_parse *p);
int		ft_check_n_vector(double x, double y, double z);


//cylinder_lst.c
void	ft_free_cy(t_parse *p);
void	ft_cyadd_back(t_cy **lst, t_cy *new);
void	ft_cyadd_front(t_cy **lst, t_cy *new);
t_cy	*ft_cynew(t_aux	params);
int		ft_cysize(t_cy *lst);


//cylinder_parsing.c
int		ft_parse_cylinder(char **sp, t_parse *p);

//t_vec_ops_1.c
t_vec	cross(t_vec a, t_vec b);
double	vlen(t_vec v);
t_vec	norm(t_vec v);
t_vec	scale(double f, t_vec v);
t_vec	add(t_vec a, t_vec b);
t_vec	sub(t_vec a, t_vec b);
double	dot(t_vec a, t_vec b);

//ray_tracer.c
t_ray	ft_calc_ray(int i, int j, t_parse *pr);
uint32_t	get_closest_color(t_parse	*p);
int		ft_colission(t_ray ray, t_parse *pr, int x, int j);

//sphere_colission.c
int	sphere_colission(t_ray ray, t_parse *pr);
int	ft_there_is_colission_sp(t_ray ray, t_sph *sp);
double	ft_calc_det(t_ray ray, t_sph *sp);
int	ft_calc_intersection_sp(t_ray ray, t_sph *sp, double d);
int	ft_calc_point_sp(double t1, double t2, t_ray ray, t_sph *sp);

void ft_printcolor(t_color c);

//sphere_light.c
void	light_calc(t_hit *hit, t_parse *p);
t_color diffuse(t_hit *hit, t_parse *p);
t_color ambient(t_hit *hit, t_parse *p);

//shadow.c
int	sp_shadow(t_ray sh, t_parse *p);
int	sp_shadow_intersects(t_ray sh, t_sph *sp, int max);
int	is_in_shadow(t_hit *hit, t_parse *p);
int	pl_shadow(t_ray sh, t_parse *p);

uint32_t	rgb_to_hex_alpha(t_color color);

//hit_lst.c
void	ft_free_hit(t_hit *p);
void	ft_hitadd_back(t_hit **lst, t_hit *new);
void	ft_hitadd_front(t_hit **lst, t_hit *new);
t_hit	*ft_hitnew(t_vec hit, t_color color, t_vec n, int m);
int		ft_hitsize(t_hit *lst);
void	print_hit_list(t_hit *hit_lst);

//plane_colission.c
int	plane_colission(t_ray ray, t_parse *pr);
int	ft_there_is_colission_pl(t_ray ray, t_pl *pl);

//cylinder_colission.c
t_vec	calc_normal_cy(t_cy *cy);
int	cylinder_colission(t_ray ray, t_parse *pr);
int	lateral_colission(t_ray ray, t_cy *cy);
int	calc_lateral_colission(t_ray ray, t_cy *cy, t_vec r);
int	cy_colission_point(t_ray ray, t_cy *cy, double t1, double t2);
int	cy_both_positive(t_ray ray, t_cy *cy, t_vec p1, t_vec p2);
int	last_case(t_ray ray, t_cy *cy, t_vec p1, t_vec p2);
int	ft_there_is_colission_cy(t_ray ray, t_cy *cy);


//render.c
uint32_t	render(t_parse *pr, int width, int height);
t_vec	estimate_normal(t_vec pos, t_parse *pr);
t_collision	raycast(t_ray ray, t_parse *pr);


//sdf_1.c
double	sp_sdf(t_vec p, t_sph *sp);
double rocket(t_vec p);
double sphere(t_vec p, t_sph *sp);
double cylinder(t_vec p, t_cy *cy);
double	cy_sdf(t_vec p, t_cy *cy);
double plane(t_vec p, t_pl *pl);
double	pl_sdf(t_vec p, t_pl *pl);