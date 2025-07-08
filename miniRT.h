/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:23 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/08 20:58:52 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "MLX42/include/MLX42/MLX42.h"
# define MAX_W 800  //3840
# define MAX_H 600  //2160
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
	float	x;
	float	y;
	float	z;
}			t_vec;

/* typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}			t_vec; */

typedef struct s_sph
{
	t_vec			point;
	float			diam;
	t_color			color;
	struct s_sph	*next;
}			t_sph;

typedef struct s_pl
{
	t_vec			point;
	t_vec			n_vector;
	t_color			color;
	struct s_pl		*next;
}			t_pl;

typedef struct s_cy
{
	t_vec			point;
	t_vec			n_vector;
	float			diam;
	float			height;
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
	t_vec			lower_left;
	float			fov;
	float			as_ratio;
	float			vp_h;
	float			vp_w;
}			t_cam;

//as of now, used for passing params to cylinder node creation
typedef struct s_aux
{
	t_vec			point;
	t_vec			n_vector;
	float			diam;
	float			height;
	t_color			color;
}			t_aux;

typedef struct s_parse
{
	int		A;
	float	am_ratio;
	t_color	am_color;
	int		C;
	t_cam	*cam;
	int		L;
	t_vec	l_point;
	float	l_bright;
	t_color	l_color;
	//for the objects, we need lists(can be more than one)
	int		sp_count;
	t_sph	*sp;
	int		pl_count;
	t_pl	*pl;
	int		cy_count;
	t_cy	*cy;
	t_color	cy_color;
}			t_parse;

//ft_atof.c
float	ft_atof(char *str);


//gnl.c
char	*get_next_line(int fd);


//utils1.c
void	ft_free(char **sp);


//ambient_parsing.c
int		ft_parse_ambient(char **spline, t_parse *program);
int		ft_init_t_color_am(t_parse *program, int r, int g, int b);


//camera_parsing.c
int		ft_parse_camera(char **sp, t_parse *program);
int		ft_init_cam_origin(t_parse *program, float x, float y, float z);
int		ft_init_cam_dir(t_parse *program, float x, float y, float z);
int		ft_init_cam_fov(t_parse *program, int fov);
void	ft_init_viewport(t_parse *p);


//light parsing.c
int		ft_parse_light(char **sp, t_parse *program);
int		ft_init_t_vec_li(t_parse *program, float x, float y, float z);
int		ft_init_t_color_li(t_parse *program, int r, int g, int b);


//parsing.c
int		ft_parse_line(char *line, t_parse *program);
t_parse *ft_init_parse();
t_parse	*ft_read_file(int fd);
int		ft_check_extension(char *file);
t_parse	*ft_free_parsing(t_parse *p);
t_parse	*ft_parsing(int argc, char **argv);


//sphere_lst.c
void	ft_sphadd_back(t_sph **lst, t_sph *new);
void	ft_sphadd_front(t_sph **lst, t_sph *new);
t_sph	*ft_sphnew(t_vec p, float d, t_color c);
int		ft_sphsize(t_sph *lst);
void	ft_free_sp(t_parse *p);


//sphere_parsing.c
int	ft_parse_sphere(char **sp, t_parse *p);
int	ft_check_color(char **sp);
t_color ft_init_color(char **sp);
t_vec ft_init_vec(float x, float y, float z);
int	ft_check_point(float x, float y, float z);
int	ft_init_t_color_sp(t_parse *p, int r, int g, int b);


//plane_lst.c
void	ft_free_pl(t_parse *p);
void	ft_pladd_back(t_pl **lst, t_pl *new);
void	ft_pladd_front(t_pl **lst, t_pl *new);
t_pl	*ft_plnew(t_vec p, t_vec n, t_color c);
int		ft_plsize(t_pl *lst);


//plane_parsing.c
int		ft_parse_plane(char **sp, t_parse *p);
int		ft_check_n_vector(float x, float y, float z);


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
t_vec	norm(t_vec v);
t_vec	scale(float f, t_vec v);
t_vec	add(t_vec a, t_vec b);