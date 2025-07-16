/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:46:10 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/16 15:40:01 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	sp_light_calc(t_sph *sp, t_parse *p)
{
	t_color	diff;
	t_color	am;
	t_vec	normal;

	normal = norm(sub(sp->colission, sp->point));
	if (sp->in)
		normal = scale(-1, normal);
	if (dot(normal, norm(sub(p->l_point, sp->colission))) > 0)
		diff = sp_diffuse(sp, p, normal);
	else
	{
		diff.r = 0;
		diff.g = 0;
		diff.b = 0;
	}
	//diff = sp_diffuse(sp, p, normal);
	am = sp_ambient(sp, p);
	sp->pixel_color.r = fmin(255, diff.r + am.r);
	sp->pixel_color.g = fmin(255, diff.g + am.g);
	sp->pixel_color.b = fmin(255, diff.b + am.b);
}

t_color sp_diffuse(t_sph *sp, t_parse *p, t_vec	normal)
{
	t_color	diff;
	double	intensity;

	//printf("normal x l.point: %f\n", dot(normal, p->l_point));
	intensity = fmax(0, dot(normal, norm(sub(p->l_point, sp->colission))));
	/* if (dot(normal, p->l_point) > 0)
		intensity = fmax(0, dot(normal, p->l_point));
	else
		intensity = 0; */
	diff.r = sp->color.r * (p->l_bright) * (p->l_color.r / 255) * intensity;
	diff.g = sp->color.g * (p->l_bright) * (p->l_color.g / 255) * intensity;
	diff.b = sp->color.b * (p->l_bright) * (p->l_color.b / 255) * intensity;
	return (diff);
}

t_color sp_ambient(t_sph *sp, t_parse *p)
{
	t_color	am;

	//intensity = fmax(0, dot(normal, p->l_point));
	am.r = sp->color.r * (p->am_ratio) * (p->am_color.r / 255);
	am.g = sp->color.g * (p->am_ratio) * (p->am_color.g / 255);
	am.b = sp->color.b * (p->am_ratio) * (p->am_color.b / 255);
	return (am);
}