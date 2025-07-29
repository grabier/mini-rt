/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:33:03 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/29 18:47:40 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_plane(char **sp, t_parse *p)
{
	t_vec p1;
	t_vec p2;
	t_color	c;
	char	**sp_aux;

	//init plane point
	sp_aux = ft_split(sp[1], ',');
	if (!ft_check_point(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]), ft_atod(sp_aux[2])))
		return (printf("pl point invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	p1 = ft_init_vec(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]), ft_atod(sp_aux[2]));
	ft_free(sp_aux);
	//printf("pl_point: %f, %f, %f\n", p1.x, p1.y, p1.z);

	//init plane normal_vector
	sp_aux = ft_split(sp[2], ',');
	if (!ft_check_n_vector(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]), ft_atod(sp_aux[2])))
		return (printf("pl normal vector invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	p2 = ft_init_vec(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]), ft_atod(sp_aux[2]));
	ft_free(sp_aux);
	
	//init plane color
	sp_aux = ft_split(sp[3], ',');
	if (!ft_check_color(sp_aux))
		return (printf("pl color invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	c = ft_init_color(sp_aux);
	
	
	ft_pladd_back(&p->pl, ft_plnew(p1, p2, c));
	//printf("pl_point: %f, %f, %f\t\t", p->pl->point.x, p->pl->point.y, p->pl->point.z);
	/* if (p->pl->next == NULL)
		printf("is NULL\n"); */
	p->pl_count++;
	return (ft_free(sp_aux), ft_free(sp), 1);
}

int	ft_check_n_vector(double x, double y, double z)
{
	if (fabs(x - 2.232323) < 0.0001 || fabs(y - 2.232323) < 0.0001 || fabs(z - 2.232323) < 0.0001)
		return (0);
	if (x > 1 || x < -1 || y > 1 || y < -1 || z > 1 || z < -1)
		return (0);
	return (1);
}
