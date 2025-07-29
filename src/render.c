/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:35:47 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/29 16:48:32 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_collision raycast(t_ray ray) {
	t_collision res;
	res.depth = -1;

	double t = 0.0;
	for (int i = 0; i < 90 && t < MAX_D; i++) {
		t_vec p = add(ray.or, scale(t, ray.dir));
		//double h = fmax(rocket(p), sphere(p));
		double h = sphere(p);
		if (fabs(h) < 0.0001) {
			res.depth = t;
			break;
		}
		t += h;
	}
	return res;
}

t_vec estimate_normal(t_vec pos) {
	const double eps = 0.0005;

	double dx = rocket((t_vec){pos.x + eps, pos.y, pos.z}) - rocket((t_vec){pos.x - eps, pos.y, pos.z});
	double dy = rocket((t_vec){pos.x, pos.y + eps, pos.z}) - rocket((t_vec){pos.x, pos.y - eps, pos.z});
	double dz = rocket((t_vec){pos.x, pos.y, pos.z + eps}) - rocket((t_vec){pos.x, pos.y, pos.z - eps});

	return norm((t_vec){dx, dy, dz});
}

uint32_t render(t_parse *pr, int width, int height) {
	t_ray ray = ft_calc_ray(width, height, pr);
	t_collision col = raycast(ray);
	t_hit light;

	if (col.depth != -1) {
		t_vec n = estimate_normal(add(ray.or, scale(col.depth, ray.dir)));
		t_color c = (t_color){(n.x + 1.0) * 127.5, (n.y + 1.0) * 127.5, (n.z + 1.0) * 127.5};
		light.colission = add(ray.or, scale(col.depth, ray.dir));
		light.next = NULL;
		light.normal = n;
		light.object = 5;
		light.pixel_color = c;
		light_calc(&light, pr);
		return rgb_to_hex_alpha(light.pixel_color);
	}
	return 0xFF000000; // negro fondo
}