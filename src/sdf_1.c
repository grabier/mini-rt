/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:36:48 by gmontoro          #+#    #+#             */
/*   Updated: 2025/08/07 17:20:44 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double cylinder(t_vec p, t_cy *cy)
{
	//printf("entramous\n");
	// Vector del punto al centro
	t_vec pa = sub(p, cy->point);

	// Proyección de pa sobre el eje (v)
	double y = dot(pa, cy->n_vector);

	// Componente ortogonal al eje
	t_vec projected = sub(pa, scale(y, cy->n_vector));
	double x = vlen(projected);

	// Distancias radiales y axiales
	double dx = x - cy->r;
	//printf("cy->h: %f\n", cy->height);
	double dy = fabs(y) - cy->height / 2.0;

	// Casos según posición respecto a la tapa y pared
	double outside = fmax(dx, dy);
	double inside = fmin(fmax(dx, dy), 0.0);
	double dist = outside > 0.0 ? vlen((t_vec){fmax(dx,0.0), fmax(dy,0.0), 0}) : inside;

	return dist;
}

double sphere(t_vec p, t_sph *sp) {
	return vlen(sub(p, sp->point)) - (sp->diam / 2);
}

double plane(t_vec p, t_pl *pl) {
	return dot(sub(p, pl->point), pl->n_vector);
}

double	cy_sdf(t_vec p, t_cy *cy)
{
	double min_dist = 1e9; // o algún valor suficientemente grande
	t_cy	*aux = cy;

	//printf("22222cy->h: %f\n", cy->height);
	while(aux)
	{
		double d = cylinder(p, aux);
		if (d < min_dist && d > 0) {
			//printf("entramus\n");
			min_dist = d;
		}
		aux = aux->next;
	}
	return min_dist;
}

double	sp_sdf(t_vec p, t_sph *sp)
{
	double min_dist = 1e9; // o algún valor suficientemente grande
	t_sph	*aux = sp;

	while(aux) {
		
		double d = sphere(p, aux);
		if (d < min_dist && d > 0) {
			//printf("entramus\n");
			min_dist = d;
		}
		aux = aux->next;
	}
	return min_dist;
}

double	pl_sdf(t_vec p, t_pl *pl)
{
	double min_dist = 1e9; // o algún valor suficientemente grande
	t_pl	*aux = pl;

	while(aux) {
		
		double d = plane(p, aux);
		if (d < min_dist && d > 0) {
			//printf("entramus\n");
			min_dist = d;
		}
		aux = aux->next;
	}
	return min_dist;
}

double rocket(t_vec p) {
	double x = p.x, y = p.y, z = p.z;

	double f = pow(x, 2.0) * pow(y, 2.0)
		+ 0.5 * pow(x, 2.0) * pow(z, 2.0)
		- 1.0 * pow(x, 2.0)
		+ pow(x, 4.0)
		+ pow(y, 2.0) * pow(z, 2.0)
		- 1.0 * pow(y, 3.0)
		+ 0.5 * pow(y, 4.0)
		- 1.0 * pow(z, 2.0)
		+ pow(z, 4.0)
		+ 1.0 / 3.0;

	t_vec grad;
	grad.x = 2.0 * x * pow(y, 2.0)
		+ x * pow(z, 2.0)
		- 2.0 * x
		+ 4.0 * pow(x, 3.0);

	grad.y = 2.0 * pow(x, 2.0) * y
		+ 2.0 * y * pow(z, 2.0)
		- 3.0 * pow(y, 2.0)
		+ 2.0 * pow(y, 3.0);

	grad.z = pow(x, 2.0) * z
		+ 2.0 * pow(y, 2.0) * z
		- 2.0 * z
		+ 4.0 * pow(z, 3.0);

	return f / vlen(grad);
}
