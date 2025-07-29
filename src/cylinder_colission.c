/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_colission.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:17:14 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/29 16:50:35 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	calc_normal_cy(t_cy *cy)
{
	t_vec	aux;
	
	/* if (cy->mcol == 0)
	{
		aux = sub(cy->colission, cy->point);
		return (norm(sub(aux, scale(dot(aux, cy->n_vector), cy->n_vector))));
	} */
	aux = sub(cy->colission, cy->point);
	return (norm(sub(aux, scale(dot(aux, cy->n_vector), cy->n_vector))));
}

int	cylinder_colission(t_ray ray, t_parse *pr, int x, int j)
{
	t_cy	*aux;
	int		intersects;
	t_vec	normal;
	
	aux = pr->cy;
	intersects = 0;
	(void)x;
	(void)j;
	while (aux)
	{
		if (ft_there_is_colission_cy(ray, aux))
		{
			intersects++;
			normal = calc_normal_cy(aux);
			/* if (aux->in)
				normal = scale(-1, normal); */
			ft_hitadd_back(&pr->hit, ft_hitnew(aux->colission, aux->color, normal, 2));
		//	mlx_put_pixel(aux->diffuse, x, j, get_closest_color(pr));
		}
		aux = aux->next;
	}
	return (intersects);
}

int	ft_there_is_colission_cy(t_ray ray, t_cy *cy)
{
	if (lateral_colission(ray, cy))
		return (1);
	/* if (top_colission(ray, cy))
		return (1);
	if (base_colission(ray, cy))
		return (1); */
	return (0);
}

int	lateral_colission(t_ray ray, t_cy *cy)
{
	t_vec	v1;
	t_vec	v2;
	t_vec	res;

	v1 = sub(ray.dir, (scale(dot(ray.dir, cy->n_vector), cy->n_vector)));
	res = sub(ray.or, cy->point);
	v2 = sub(res, scale(dot(res, cy->n_vector), cy->n_vector));
	res.x = dot(v1, v1);
	res.y = 2 * dot(v1, v2);
	res.z = dot(v2, v2) - (cy->r * cy->r);
	if (calc_lateral_colission(ray, cy, res))
		return (1);
	return (0);
}

int	calc_lateral_colission(t_ray ray, t_cy *cy, t_vec r)
{
	double	t1;
	double	t2;
	t_vec	p1;
	//t_vec	p2;

	t1 = (-r.y + sqrt((r.y * r.y) - (4 * r.x * r.z))) / (2 * r.x);
	t2 = (-r.y - sqrt((r.y * r.y) - (4 * r.x * r.z))) / (2 * r.x);
	p1 = add(ray.or, scale(t1, ray.dir));
	//p2 = add(ray.or, scale(t1, ray.dir));
	if (t1 <= 0 && t2 <= 0)
		return (0);
	if (t1 > 0 && t2 < 0)
	{
		if ((dot(sub(ray.dir, cy->point), cy->n_vector)) >= ((-1 * cy->height) / 2)
			&& (dot(sub(ray.dir, cy->point), cy->n_vector)) <= cy->height / 2)
		{
			cy->colission = p1;
			cy->mcol = 0;
		}
		return (1);
	}
	if (cy_colission_point(ray, cy, t1, t2))
		return (1);
	return (0);
}

int	cy_colission_point(t_ray ray, t_cy *cy, double t1, double t2)
{
	t_vec	p1;
	t_vec	p2;

	p1 = add(ray.or, scale(t1, ray.dir));
	p2 = add(ray.or, scale(t1, ray.dir));
	if (t2 > 0 && t1 < 0)
	{
		p1 = add(ray.or, scale(t2, ray.dir));
		if ((dot(sub(ray.dir, p1), cy->n_vector)) >= ((-1 * cy->height) / 2)
			&& (dot(sub(ray.dir, p1), cy->n_vector)) <= (cy->height / 2))
		{
			cy->colission = p2;
			cy->mcol = 0;
		}
		return (1);
	}
	if (t1 > 0 && t2 > 0)
	{
		if (cy_both_positive(ray, cy, p1, p2))
			return (1);
		return (0);
	}
	return (0);
}

int	cy_both_positive(t_ray ray, t_cy *cy, t_vec p1, t_vec p2)
{

	if ((dot(sub(ray.dir, p1), cy->n_vector)) < ((-1 * cy->height) / 2)
		|| (dot(sub(ray.dir, p1), cy->n_vector)) > cy->height / 2)
	{
		if ((dot(sub(ray.dir, p2), cy->n_vector)) <= ((-1 * cy->height) / 2)
		|| (dot(sub(ray.dir, p2), cy->n_vector)) >= cy->height / 2)
			return (0);
	}
	if ((dot(sub(ray.dir, p1), cy->n_vector)) < ((-1 * cy->height) / 2)
		||(dot(sub(ray.dir, p1), cy->n_vector)) > cy->height / 2)
	{
		cy->colission = p2;
		cy->mcol = 0;
		return (1);
	}
	if ((dot(sub(ray.dir, p2), cy->n_vector)) <= ((-1 * cy->height) / 2)
		&& (dot(sub(ray.dir, p2), cy->n_vector)) >= cy->height / 2)
	{
		cy->colission = p1;
		cy->mcol = 0;
		return (1);
	}
	return (last_case(ray, cy, p1, p2));
}

int	last_case(t_ray ray, t_cy *cy, t_vec p1, t_vec p2)
{
	if (vlen(sub(p1, ray.or)) > vlen(sub(p2, ray.or)))
			cy->colission = p2;
	else
			cy->colission = p1;
	cy->mcol = 0;
	return (1);
}

