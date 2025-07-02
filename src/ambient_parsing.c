/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:42:04 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/02 16:38:12 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_init_t_color_am(t_parse *program, int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		return (0);
	program->am_color.r = (unsigned char)r;
	program->am_color.g = (unsigned char)g;
	program->am_color.b = (unsigned char)b;
	return (1);
}

int	ft_parse_ambient(char **spline, t_parse *program)
{
	float	f;
	char	**sp_aux;
	int		aux;
	
	f = ft_atof(spline[1]);//2.232323 for error
	//printf("ambient ratio: %f\n", f );
	if(f < 0.0 || f > 1.0 || fabs(f - 2.232323) < 0.0001)
		return (printf("ambient ratio invalid\n"), ft_free(spline), 0);
	program->am_ratio = f;
	sp_aux = ft_split(spline[2], ',');
	//printf("spline: %s\n", sp_aux[1]);
	if (!ft_check_color(sp_aux))//check if valid for int
		return (printf("ambient color out invalid\n"), ft_free(sp_aux), ft_free(spline), 0);
	aux = ft_atoi(sp_aux[0]);
	if(!ft_init_t_color_am(program, aux, ft_atoi(sp_aux[1]), ft_atoi(sp_aux[2])))//check if in the rgb range
		return (printf("ambient color invalid\n"), ft_free(sp_aux), ft_free(spline), 0);
	if(spline[3] != NULL)
		return (ft_free(sp_aux), 0);
	program->A++;
	return (ft_free(sp_aux), ft_free(spline), 1);
}
