/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:53:11 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/22 16:39:46 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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
	/* if (i == 800 && j == 600){
		
		printf("R: ");
		printv(pr->cam->hor);
		printf("U: ");
		printv(pr->cam->ver);
		printf("vector no normalizado: ");
		printv(dir);
	} */
	return (ray);
}

uint32_t	get_closest_color(t_parse	*p)
{
	t_hit	*aux;
	t_hit	*closest;
	double	distance;

	aux = p->hit;
	closest = NULL;
	distance = __DBL_MAX__;
	while (aux)
	{
		if (distance > vlen(sub(aux->colission, p->cam->origin)))
		{
			distance = vlen(sub(aux->colission, p->cam->origin));
			closest = aux;
		}
		aux = aux->next;
	}

	return (rgb_to_hex_alpha(closest->pixel_color));
}

int		ft_sp_intersection(t_ray ray, t_parse *pr, int x, int j)
{
	t_sph	*aux;
	int		i;
	int		intersects;

	i = 0;
	intersects = 0;
	aux = pr->sp;
	ft_free_hit(pr->hit);
	pr->hit = NULL;
	while (aux)
	{
		if (ft_there_is_colission_sp(ray, aux))
		{
			intersects++;
			//list of intersections. we will choose the closest to cam
			sp_light_calc(aux, pr);
			/* printf("pixel color: \t");
			ft_printcolor(pr->sp->pixel_color); */
		}
		aux = aux->next;
		i++;
	}
	/* if (x == 800 && j == 600) 
		print_hit_list(pr->hit); */
	//printf("number of colissions for pixel(%i, %i): %i\n", x, j, intersects);
	if (pr->hit)
		mlx_put_pixel(pr->img, x, j, get_closest_color(pr));
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
