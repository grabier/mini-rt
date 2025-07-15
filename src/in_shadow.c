/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:43:16 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/15 18:52:05 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_in_shadow(t_vec c, t_parse *p)
{
	t_ray	r;

	r.or = c;
	r.dir = norm(sub(p->l_point, c));
	printf("shadows: ray.or: \t");
	printv(r.or);
	printf("ray.dir: \t");
	printv(r.dir);
	if (ft_sp_intersection(r, p))//we calculating for spheres only
		return (1);
	else
		return (0);
}