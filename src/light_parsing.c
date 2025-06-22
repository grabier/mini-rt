/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:06:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/06/22 15:37:47 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_light(char **sp, t_parse *program)
{
	char	**sp_aux;
	char	**sp_aux2;
	float	f;
	int		n;

	printf("sp1: %s\n", sp[0]);
	sp_aux = ft_split(sp[1], ',');
	f = ft_atof(sp_aux[0]);
	if(!ft_init_t_point_li(program, f, ft_atof(sp_aux[1]), ft_atof(sp_aux[2])))
		return (printf("light point invalid\n"), ft_free(sp_aux), 0);
	f = ft_atof(sp[2]);//2.232323 for error
	if(f < 0.0 || f > 1.0 || f == 2.232323)
		return (printf("light ratio invalid\n"), 0);
	program->l_bright = f;
	if (!sp[3])
		return (ft_free(sp_aux), ft_free(sp), 1);
	sp_aux2 = ft_split(sp[3], ',');
	if (!ft_check_color(sp_aux2))//check if valid for int
		return (printf("light color invalid\n"), ft_free(sp_aux), ft_free(sp_aux2), ft_free(sp), 0);
	n = ft_atoi(sp_aux2[0]);
	if(!ft_init_t_color_li(program, n, ft_atoi(sp_aux2[1]), ft_atoi(sp_aux2[2])))
		return (printf("light color invalid\n"), ft_free(sp_aux), ft_free(sp_aux2), ft_free(sp), 0);
	if(sp[4] != NULL || sp_aux[3] != NULL || sp_aux2[3] != NULL)
		return (ft_free(sp_aux), ft_free(sp_aux2), ft_free(sp), 0);
	program->L++;
	return (ft_free(sp_aux),ft_free(sp_aux2), ft_free(sp), 1);
}

int	ft_init_t_point_li(t_parse *program, float x, float y, float z)
{
	if (x == 2.232323 || y == 2.232323 || z == 2.232323)
		return (0);
	program->l_point.x = x;
	program->l_point.y = y;
	program->l_point.z = z;
	return (1);
}

int	ft_init_t_color_li(t_parse *program, int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		return (0);
	program->l_color.r = (unsigned char)r;
	program->l_color.g = (unsigned char)g;
	program->l_color.b = (unsigned char)b;
	return (1);
}