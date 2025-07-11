/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:26:21 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/08 21:25:57 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_cylinder(char **sp, t_parse *p)
{
	t_aux	a;
	char	**sp_aux;

	//printf("entra al CYLINDERO\n");
	sp_aux = ft_split(sp[1], ',');
	if (!ft_check_point(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]), ft_atod(sp_aux[2])))
		return (printf("cy point invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	a.point = ft_init_vec(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]), ft_atod(sp_aux[2]));
	ft_free(sp_aux);
	
	sp_aux = ft_split(sp[2], ',');
	if (!ft_check_n_vector(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]), ft_atod(sp_aux[2])))
		return (printf("cy normal vector invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	a.n_vector = ft_init_vec(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]), ft_atod(sp_aux[2]));
	ft_free(sp_aux);
	//printf("sale dle CYLINDERO\n");
	
	a.diam = ft_atod(sp[3]);
	if (a.diam <= 0 || fabs(a.diam - 2.232323) < 0.0001)
		return (printf("cy diam invalid\n"), ft_free(sp), 0);

	a.height = ft_atod(sp[4]);
	if (a.diam <= 0 || fabs(a.diam - 2.232323) < 0.0001)
		return (printf("cy height invalid\n"), ft_free(sp), 0);

	sp_aux = ft_split(sp[5], ',');
	if (!ft_check_color(sp_aux))
		return (printf("cy color invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	a.color = ft_init_color(sp_aux);
	ft_cyadd_back(&p->cy, ft_cynew(a));
	p->cy_count++;
	/* printf("cy_n_vec: %f, %f, %f\n\n", p->cy->n_vector.x, p->cy->n_vector.y, p->cy->n_vector.z);
	if (p->cy->next == NULL)
		printf("is NULL\n"); */
	//printf("sale dle CYLINDERO\n");
	return (ft_free(sp_aux), ft_free(sp), 1);
}
