/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:23 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/02 18:23:47 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "MLX42/include/MLX42/MLX42.h"

#pragma once

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}			t_color;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}			t_point;

typedef struct s_sph
{
	t_point			point;
	float			diam;
	t_color			color;
	struct s_sph	*next;
}			t_sph;

typedef struct s_pl
{
	t_point			point;
	t_point			n_vector;
	t_color			color;
	struct s_pl		*next;
}			t_pl;

typedef struct s_cy
{
	t_point			point;
	t_point			n_vector;
	float			diam;
	float			height;
	t_color			color;
	struct s_cy		*next;
}			t_cy;

//as of now, used for passing params to cylinder node creation
typedef struct s_aux
{
	t_point			point;
	t_point			n_vector;
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
	t_point	cam_point;
	t_point	cam_vector;
	int		cam_fov;
	int		L;
	t_point	l_point;
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
int		ft_init_t_point_cm(t_parse *program, float x, float y, float z);
int		ft_init_t_point_cmn(t_parse *program, float x, float y, float z);
int		ft_init_cam_fov(t_parse *program, int fov);


//light parsing.c
int		ft_parse_light(char **sp, t_parse *program);
int		ft_init_t_point_li(t_parse *program, float x, float y, float z);
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
t_sph	*ft_sphnew(t_point p, float d, t_color c);
int		ft_sphsize(t_sph *lst);
void	ft_free_sp(t_parse *p);


//sphere_parsing.c
int	ft_parse_sphere(char **sp, t_parse *p);
int	ft_check_color(char **sp);
t_color ft_init_color(char **sp);
t_point ft_init_point(float x, float y, float z);
int	ft_check_point(float x, float y, float z);
int	ft_init_t_color_sp(t_parse *p, int r, int g, int b);


//plane_lst.c
void	ft_free_pl(t_parse *p);
void	ft_pladd_back(t_pl **lst, t_pl *new);
void	ft_pladd_front(t_pl **lst, t_pl *new);
t_pl	*ft_plnew(t_point p, t_point n, t_color c);
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