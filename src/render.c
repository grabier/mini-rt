/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:35:47 by gmontoro          #+#    #+#             */
/*   Updated: 2025/08/07 17:24:45 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double scene_sdf(t_vec p, t_parse *pr)
{
	return (fmin(pl_sdf(p, pr->pl), fmin(sp_sdf(p, pr->sp), cy_sdf(p, pr->cy))));
}

t_collision raycast(t_ray ray, t_parse *pr)
{
	t_collision res;
	res.depth = -1;
	double h;
	double t = 0.0;
	
	for (int i = 0; i < 128 && t < MAX_D; i++) {
		t_vec p = add(ray.or, scale(t, ray.dir));
		h = scene_sdf(p, pr);
		if (fabs(h) < 0.001) {
			res.depth = t;
			break;
		}
		t += h;
	}
	return res;
}


t_vec estimate_normal(t_vec pos, t_parse *pr)
{
	const double eps = 0.001;  // Reduced epsilon for more precise normals
	
	// Sample SDF at 6 points around pos
	double center = scene_sdf(pos, pr);
	double nx = scene_sdf((t_vec){pos.x + eps, pos.y, pos.z}, pr) - center;
	double ny = scene_sdf((t_vec){pos.x, pos.y + eps, pos.z}, pr) - center;
	double nz = scene_sdf((t_vec){pos.x, pos.y, pos.z + eps}, pr) - center;
	
	t_vec n = (t_vec){nx/eps, ny/eps, nz/eps};
	double len = sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
	
	// Only normalize if length is significant
	if (len > 1e-6) {
		return (t_vec){n.x/len, n.y/len, n.z/len};
	}
	
	// Return default normal if normalization fails
	printf("Warning: Zero normal, pos=(%f,%f,%f)\n", pos.x, pos.y, pos.z);
	return (t_vec){0, 0, 1};  // Changed default to Z direction
}

uint32_t render(t_parse *pr, int width, int height)
{
	t_ray ray = ft_calc_ray(width, height, pr);
	t_collision col = raycast(ray, pr);
	
	if (col.depth != -1) {
		t_vec hit_point = add(ray.or, scale(col.depth, ray.dir));
		t_vec n = estimate_normal(hit_point, pr);
		// Visualize normal components directly
		t_color c = (t_color){
			(fabs(n.x)) * 255,
			(fabs(n.y)) * 255,
			(fabs(n.z)) * 255 
		};
		return rgb_to_hex_alpha(c);
	}
	return 0xFF000000;  // Black background
}