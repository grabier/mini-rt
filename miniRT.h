/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:23 by gmontoro          #+#    #+#             */
/*   Updated: 2025/06/30 18:08:02 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

#pragma once

//parsing.c
//am_l-----> ambient lighting


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
	int		s;
	t_sph	*sp;
	int		p;
	t_point	pl_point;
	t_point	pl_vector;
	t_color	pl_color;
	int		cy;
	t_point	cy_point;
	t_point	cy_vector;
	float	cy_diam;
	float	cy_height;
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
int		ft_check_color(char **sp);

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
t_parse	*ft_parsing(int argc, char **argv);

//sphere_lst.c
void	ft_sphadd_back(t_sph **lst, t_sph *new);
void	ft_sphadd_front(t_sph **lst, t_sph *new);
t_sph	*ft_sphnew(t_point p, float d, t_color c);
int		ft_sphsize(t_sph *lst);
void	ft_free_sp(t_parse *p);

//sphere_parsing.c
int	ft_parse_sphere(char **sp, t_parse *p);
int	ft_check_color_sp(char **sp);
t_color ft_init_sp_color(char **sp);
t_point ft_init_p_sp(float x, float y, float z);
int	ft_check_point(float x, float y, float z);
int	ft_init_t_color_sp(t_parse *p, int r, int g, int b);