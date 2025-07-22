/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_colission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:16:58 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/22 17:25:28 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	sphere_colission(t_ray ray, t_parse *pr)
{
	t_sph	*aux;
	int		intersects;
	t_vec	normal;
	
	aux = pr->sp;
	intersects = 0;
	while (aux)
	{
		if (ft_there_is_colission_sp(ray, aux))
		{
			intersects++;
			normal = norm(sub(aux->colission, aux->point));
			if (aux->in)
				normal = scale(-1, normal);
			ft_hitadd_back(&pr->hit, ft_hitnew(aux->colission, aux->color, normal, 0));
		}
		aux = aux->next;
	}
	return (intersects);
}

int	ft_there_is_colission_sp(t_ray ray, t_sph *sp)
{
	double	det;

	det = ft_calc_det(ray, sp);
	//printf("det: %f\n", det);
	//printv(ray.dir);
	if (det > 0)
	{
		if (ft_calc_intersection_sp(ray, sp, det))
			return (1);
	}
	return (0);
}
double	ft_calc_det(t_ray ray, t_sph *sp)//h² - ac->determinante
{
	double	h;
	double	a;
	double	c;
	t_vec	aux;
	
	/* 	printf("ray.dir: \t");
	printv(ray.dir);
	printf("O - S: \t");
	printv(sub(ray.or, sp->point)); */
	h = dot(ray.dir, sub(ray.or, sp->point));
	a = dot(ray.dir, ray.dir);
	/* printf("a= %f\n", a);
	printf("h= %f\n", h); */
	aux = sub(ray.or, sp->point);
	//aux = add(sp->point, scale(-1, ray.or));
	c = dot(aux, aux) - ((sp->diam / 2) * (sp->diam / 2));
	//printf("c= %f\n", c);
	return (h * h - a * c);
}

int	ft_calc_intersection_sp(t_ray ray, t_sph *sp, double d)
{
	double	a;
	double	h;
	double	t1;
	double	t2;

	h = dot(ray.dir, sub(ray.or, sp->point));
	a = dot(ray.dir, ray.dir);
	t1 = (-h + sqrt(d)) / a;
	//printf("t1: %f\t", t1);
	t2 = (-h - sqrt(d)) / a;
	//printf("t2: %f\n", t2);
	return (ft_calc_point_sp(t1, t2, ray, sp));
}

int	ft_calc_point_sp(double t1, double t2, t_ray ray, t_sph *sp)
{
	//double	t;
	t_vec	p1;
	t_vec	p2;

	//printf("t1: %f, t2: %f\n", t1, t2);
	if (t1 > 0 && t2 > 0)//sphere in front of cam
	{
		p1 = add(ray.or, scale(t1, ray.dir));
		p2 = add(ray.or, scale(t2, ray.dir));
		if (vlen(sub(p1, ray.or)) > vlen(sub(p2, ray.or)))
			sp->colission = p2;
		else
			sp->colission = p1;
		return (1);
	}
	if (t1 > 0 && t2 < 0)
	{
		p1 = add(ray.or, scale(t1, ray.dir));
		sp->colission = p1;
		sp->in = 1;
		return (1);
	}
	if (t2 > 0 && t1 < 0)
	{
		p1 = add(ray.or, scale(t2, ray.dir));
		sp->in = 1;
		sp->colission = p1;
		return (1);
	}
	return (0);
}