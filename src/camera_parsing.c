/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:42:55 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/09 17:57:02 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_camera(char **sp, t_parse *program)
{
	char	**sp_aux;
	char	**sp_aux2;
	double	aux;

	program->cam = malloc(sizeof(t_cam));
	sp_aux = ft_split(sp[1], ',');
	aux = ft_atod(sp_aux[0]);
	if(!ft_init_cam_origin(program, aux, ft_atod(sp_aux[1]), ft_atod(sp_aux[2])))//check if in the rgb range
		return (printf("camera viewpoint invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	sp_aux2 = ft_split(sp[2], ',');
	aux = ft_atod(sp_aux2[0]);
	if(!ft_init_cam_dir(program, aux, ft_atod(sp_aux2[1]), ft_atod(sp_aux2[2])))//check if in the rgb range
		return (printf("camera orient vector invalid\n"), ft_free(sp_aux), ft_free(sp_aux2), 0);
	if (!ft_init_cam_fov(program, ft_atoi(sp[3])))
		return (printf("camera fov invalid\n"), ft_free(sp_aux), ft_free(sp_aux2), ft_free(sp), 0);
	if(sp[4] != NULL || sp_aux[3] != NULL || sp_aux2[3] != NULL)
		return (ft_free(sp_aux), ft_free(sp_aux2), ft_free(sp), 0);
	ft_init_viewport(program);
	program->C++;
	return (ft_free(sp_aux),ft_free(sp_aux2), ft_free(sp), 1);
}

void	ft_init_viewport(t_parse *p)
{
	t_vec	aux1;
	t_vec	aux2;
	
	p->cam->vp_h = 2 * tan((double) (p->cam->fov / 2));
	//printf("vp_h parsing:  %f\t", p->cam->vp_h);
	p->cam->vp_w = p->cam->vp_h * ((double)MAX_W / (double)MAX_H);
	//printf("vp_w parsing:  %f\n", ((double)MAX_W / (double)MAX_H));
	p->cam->center = add(p->cam->origin, p->cam->fw);
	p->cam->hor = scale(p->cam->vp_w, p->cam->right);
	p->cam->ver = scale(p->cam->vp_h, p->cam->up);
	aux1 = scale(-0.5, p->cam->hor);
	aux2 = scale(-0.5, p->cam->ver);
	p->cam->ll = add(p->cam->center, aux1);
	p->cam->ll = add(p->cam->ll, aux2);
}

int	ft_init_cam_origin(t_parse *program, double x, double y, double z)
{
	if (fabs(x - 2.232323) < 0.0001 || fabs(y - 2.232323) < 0.0001 || fabs(z - 2.232323) < 0.0001)
		return (0);
	program->cam->origin.x = x;
	program->cam->origin.y = y;
	program->cam->origin.z = z;
	program->cam->as_ratio = (double)(MAX_W / MAX_H);
	return (1);
}

int	ft_init_cam_dir(t_parse *program, double x, double y, double z)
{
	t_vec	up;

	if (fabs(x - 2.232323) < 0.0001 || fabs(y - 2.232323) < 0.0001 || fabs(z - 2.232323) < 0.0001)
		return (0);
	if (x > 1 || x < -1 || y > 1 || y < -1 || z > 1 || z < -1)
		return (0);
	program->cam->fw.x = x;
	program->cam->fw.y = y;
	program->cam->fw.z = z;
	up.x = 0;
	up.y = 1;
	up.z = 0;
	program->cam->right = norm(cross(up, program->cam->fw));
	program->cam->up = norm(cross(program->cam->fw, program->cam->right));
	return (1);
}

int	ft_init_cam_fov(t_parse *program, int fov)
{
	if (fov == -1 || fov < 0 || fov > 180)
		return (0);
	program->cam->fov = fov * (PI / 180);
	program->cam->fov = fov * (PI / 180);
	return (1);
}