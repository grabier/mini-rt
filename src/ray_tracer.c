/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:53:11 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/24 16:36:43 by gmontoro         ###   ########.fr       */
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
	light_calc(closest, p);//lights r now calc'd here, and only for the closest intersection(did a few tests, doesnt seem to make it faster)
	return (rgb_to_hex_alpha(closest->pixel_color));
}

int		ft_colission(t_ray ray, t_parse *pr, int x, int j)//changed to loop through all object lists, and now we calc the closest when deciding the color
{
	int		intersects;

	intersects = 0;
	ft_free_hit(pr->hit);
	pr->hit = NULL;
	intersects += sphere_colission(ray, pr);
	intersects += plane_colission(ray, pr);
	/* if (x == 800 && j == 600) 
		print_hit_list(pr->hit); */
	//printf("number of colissions for pixel(%i, %i): %i\n", x, j, intersects);
	if (pr->hit)
		mlx_put_pixel(pr->img, x, j, get_closest_color(pr));//we calc the closest here now
	return (intersects);
}
