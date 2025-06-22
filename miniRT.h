/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:23 by gmontoro          #+#    #+#             */
/*   Updated: 2025/06/21 20:02:26 by gmontoro         ###   ########.fr       */
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
	int		s;
	t_point	sph_point;
	float	sph_diam;
	t_color	sph_color;
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
int		init_t_color_am(t_parse *program, int r, int g, int b);
int		check_color(char **sp);

//camera_parsing.c
int		ft_parse_camera(char **sp, t_parse *program);
int		init_t_point_cm(t_parse *program, float x, float y, float z);
int		init_t_point_cmn(t_parse *program, float x, float y, float z);
int		init_cam_fov(t_parse *program, int fov);

//parsing.c
int		ft_parse_line(char *line, t_parse *program);
t_parse *ft_init_parse();
t_parse	*ft_read_file(int fd);
int		ft_check_extension(char *file);
t_parse	*ft_parsing(int argc, char **argv);

