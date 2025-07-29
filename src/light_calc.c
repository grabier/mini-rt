/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:46:10 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/27 18:26:38 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	light_calc(t_hit *hit, t_parse *p)
{
	t_color	diff;
	t_color	am;

	diff = diffuse(hit, p);
	am = ambient(hit, p);
	hit->pixel_color.r = fmin(255, diff.r + am.r);
	hit->pixel_color.g = fmin(255, diff.g + am.g);
	hit->pixel_color.b = fmin(255, diff.b + am.b);
}

t_color diffuse(t_hit *hit, t_parse *p)
{
	t_color	diff;
	double	intensity;

	if (hit->object == 1 && dot(hit->normal, norm(sub(p->l_point, hit->colission))) < 0)//normals r a bit fucked up when talking about planes(hit->object == 1)
		hit->normal = scale(-1, hit->normal);										//since they can have 2 normals
	if (dot(hit->normal, norm(sub(p->l_point, hit->colission))) > 0)
		intensity = fmax(0, dot(hit->normal, norm(sub(p->l_point, hit->colission))));
	else
		intensity = 0;
	//if (is_in_shadow(hit, p))//shadow rays r now only calc'd for the closest hit
		//intensity = 0;
	diff.r = hit->pixel_color.r * (p->l_bright) * (p->l_color.r / 255) * intensity;
	diff.g = hit->pixel_color.g * (p->l_bright) * (p->l_color.g / 255) * intensity;
	diff.b = hit->pixel_color.b * (p->l_bright) * (p->l_color.b / 255) * intensity;
	return (diff);
}

t_color ambient(t_hit *hit, t_parse *p)
{
	t_color	am;

	//intensity = fmax(0, dot(normal, p->l_point));
	am.r = hit->pixel_color.r * (p->am_ratio) * (p->am_color.r / 255);
	am.g = hit->pixel_color.g * (p->am_ratio) * (p->am_color.g / 255);
	am.b = hit->pixel_color.b * (p->am_ratio) * (p->am_color.b / 255);
	return (am);
}