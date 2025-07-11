/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:53:11 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/10 19:46:05 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	ft_calc_det(t_ray ray, t_sph *sp)//h² - ac->determinante
{
	double	h;
	double	a;
	double	c;
	t_vec	aux;

	//printv(ray.dir);
	h = dot(ray.dir, sub(ray.or, sp->point));
	a = dot(ray.dir, ray.dir);
	//printf("a= %f\n", a);
	aux = sub(ray.or, sp->point);
	//aux = add(sp->point, scale(-1, ray.or));
	c = dot(aux, aux) - ((sp->diam / 2) * (sp->diam / 2));
	//printf("c= %f\n", c);
	return (h * h - a * c);
}

t_vec	ft_get_ray_point(t_ray ray, double t)
{
	t_vec	v;

	v = add(ray.or, scale(t, ray.dir));
	return (v);
}

int	ft_calc_point_sp(double t1, double t2, t_ray ray, t_sph *sp)
{
	double	t;

	//printf("t1: %f, t2: %f\n", t1, t2);
	if (t1 > 0 && t2 > 0)//sphere in front of cam
	{
		if (t1 > t2)
			t = t2;
		else
			t = t1;
		//printf("llega aki???\n");
		sp->colission = ft_get_ray_point(ray, t);
		return (1);
	}
	return (0);
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
	t2 = (-h - sqrt(d)) / a;
	return (ft_calc_point_sp(t1, t2, ray, sp));
}

int	ft_intersects_sp(t_ray ray, t_sph *sp)
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

int		ft_sp_intersection(t_ray ray, t_parse *pr)
{
	t_sph	*aux;
	int		i;
	int		intersects;

	i = 0;
	intersects = 0;
	aux = pr->sp;
	while (i < pr->sp_count)
	{
		if (ft_intersects_sp(ray, aux))
			intersects++;
		aux = aux->next;
		i++;
	}
	//printf("number of colissions: %i\n", intersects);
	return (intersects);
}

t_ray	ft_calc_ray(int i, int j, t_parse *pr)
{
	double	u;
	double	v;
	t_vec	dir;
	t_ray	ray;

	u = (i + 0.5) / MAX_W;
	v = (j + 0.5) / MAX_H;
	dir = add(add(pr->cam->ll, scale(u, pr->cam->hor)), scale(v, pr->cam->ver));
	ray.or = pr->cam->origin;
	ray.dir = norm(dir);
	if (i == 800 && j == 600){
		printf("u = %f. v = %f\n", u, v);
		printf("LL: ");
		printv(pr->cam->ll);
		printf("R: ");
		printv(pr->cam->hor);
		printf("U: ");
		printv(pr->cam->ver);
		printf("vector no normalizado: ");
		printv(dir);
	}
	return (ray);
}