/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:43:16 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/22 19:10:21 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	sp_shadow_intersects(t_ray sh, t_sph *sp, int max)
{
	double	det;
	double	a;
	double	h;
	double	t;

	det = ft_calc_det(sh, sp);
	if (det > 0)
	{
		h = dot(sh.dir, sub(sh.or, sp->point));
		a = dot(sh.dir, sh.dir);
		t = (-h - sqrt(det)) / a;
		if (t > 0.0001 && t < max)
			return (1);
		t = (-h + sqrt(det)) / a;
		if (t > 0.0001 && t < max)
			return (1);
	}
	return (0);
}

int	sp_shadow(t_ray sh, t_parse *p)
{
	t_sph	*aux;
	double	max;
	
	aux = p->sp;
	while (aux)
	{
		max = vlen(sub(p->l_point, sh.or));
		if (sp_shadow_intersects(sh, aux, max))
			return (1);
		aux = aux->next;
	}
	return (0);
}

int	is_in_shadow(t_hit *hit, t_parse *p)
{
	t_ray	sh;

	hit->colission = add(hit->colission, scale(0.0001, hit->normal));
	sh.or = hit->colission;
	sh.dir = norm(sub(p->l_point, sh.or));
	if (sp_shadow(sh, p))
		return (1);
	return (0);
}