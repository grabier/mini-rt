/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_colission.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:33:30 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/23 18:58:10 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	plane_colission(t_ray ray, t_parse *pr)
{
	t_pl	*aux;
	int		intersects;
	
	aux = pr->pl;
	intersects = 0;
	while (aux)
	{
		if (ft_there_is_colission_pl(ray, aux))
		{
			intersects++;
			/* if (aux->in)
				normal = scale(-1, normal); */
			ft_hitadd_back(&pr->hit, ft_hitnew(aux->colission, aux->color, aux->n_vector, 1));
		}
		aux = aux->next;
	}
	return (intersects);
}

int	ft_there_is_colission_pl(t_ray ray, t_pl *pl)
{
	double	den;
	double	t;
	
	den = dot(pl->n_vector, ray.dir);
	if (fabs(den) < 0.001)
		return (0);
	t = dot(pl->n_vector, sub(pl->point, ray.or)) / den;
	if (t > 0.001)
	{
		pl->colission = add(ray.or, scale(t, ray.dir));
		return (1);
	}
	return (0);
}
