/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:42:55 by gmontoro          #+#    #+#             */
/*   Updated: 2025/06/21 20:01:57 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_camera(char **sp, t_parse *program)
{
	char	**sp_aux;
	char	**sp_aux2;
	float	aux;

	sp_aux = ft_split(sp[1], ',');
	aux = ft_atof(sp_aux[0]);
	if(!init_t_point_cm(program, aux, ft_atof(sp_aux[1]), ft_atof(sp_aux[2])))//check if in the rgb range
		return (printf("camera viewpoint invalid\n"), ft_free(sp_aux), 0);
	sp_aux2 = ft_split(sp[2], ',');
	aux = ft_atof(sp_aux2[0]);
	if(!init_t_point_cmn(program, aux, ft_atof(sp_aux2[1]), ft_atof(sp_aux2[2])))//check if in the rgb range
		return (printf("camera orient vector invalid\n"), ft_free(sp_aux), free(sp_aux2), 0);
	if (!init_cam_fov(program, ft_atoi(sp[3])))
		return (printf("camera fov invalid\n"), ft_free(sp_aux), free(sp_aux2), 0);
	if(sp[4] != NULL || sp_aux[3] != NULL || sp_aux2[3] != NULL)
		return (ft_free(sp_aux), free(sp_aux2), 0);
	program->C++;
	return (ft_free(sp_aux),free(sp_aux2), ft_free(sp), 1);
}

int	init_t_point_cm(t_parse *program, float x, float y, float z)
{
	if (x == 2.232323 || y == 2.232323 || z == 2.232323)
		return (0);
	program->cam_point.x = x;
	program->cam_point.y = y;
	program->cam_point.z = z;
	return (1);
}

int	init_t_point_cmn(t_parse *program, float x, float y, float z)
{
	if (x == 2.232323 || y == 2.232323 || z == 2.232323)
		return (0);
	if (x > 1 || x < -1 || y > 1 || y < -1 || z > 1 || z < -1)
		return (0);
	program->cam_vector.x = x;
	program->cam_vector.y = y;
	program->cam_vector.z = z;
	return (1);
}

int	init_cam_fov(t_parse *program, int fov)
{
	if (fov == -1 || fov < 0 || fov > 180)
		return (0);
	program->cam_fov = fov;
	return (1);
}