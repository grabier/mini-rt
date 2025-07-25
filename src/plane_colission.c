/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_colission.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:33:30 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/25 18:43:43 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	plane_colission(t_ray ray, t_parse *pr, int x, int j)
{
	t_pl	*aux;
	int		intersects;
	
	aux = pr->pl;
	intersects = 0;
	(void)x;
	(void)j;
	while (aux)
	{
		if (ft_there_is_colission_pl(ray, aux))
		{
			intersects++;
			/* if (aux->in)
				normal = scale(-1, normal); */
			ft_hitadd_back(&pr->hit, ft_hitnew(aux->colission, aux->color, aux->n_vector, 1));
			//mlx_put_pixel(aux->diffuse, x, j, get_closest_color(pr));
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
