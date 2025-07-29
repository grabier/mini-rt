/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:36:48 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/29 16:37:07 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double sphere(t_vec p){
    return vlen(p) - 3.0;
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