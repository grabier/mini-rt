/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec_ops_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:31:16 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/15 17:14:39 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double vlen(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec cross(t_vec a, t_vec b)//return a vector orthogonal to a and b
{
	t_vec c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_vec norm(t_vec v)//retulrns the unitary vector for v
{
	double	l;

	l = vlen(v);
	if (l == 0)
		return (printf("Error: cannot normalize vector\n"), (t_vec){0, 0, 0});
	v.x /= l;
	v.y /= l;
	v.z /= l;
	return (v);
}

t_vec scale(double f, t_vec v)
{
	t_vec v2;
	
	v2.x = v.x * f;
	v2.y = v.y * f;
	v2.z = v.z * f;
	return (v2);
}

t_vec add(t_vec a, t_vec b)
{
	t_vec c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vec sub(t_vec a, t_vec b)
{
	t_vec c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

double	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
