/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:32:25 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/17 17:36:37 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_free(char **sp)
{
	int	i;

	i = 0;
	while (sp[i])
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}

void	printv(t_vec v)
{
	printf("x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}

void	ft_printcolor(t_color c)
{
	printf("R: %i, G: %i, B: %i\n", c.r, c.g, c.b);
}

void	start_timer(struct timeval *start)
{
	gettimeofday(start, NULL);
}

void	end_timer(struct timeval start)
{
	struct timeval end;
	gettimeofday(&end, NULL);

	long seconds = end.tv_sec - start.tv_sec;
	long microseconds = end.tv_usec - start.tv_usec;

	printf("Render time: %.6f seconds\n", seconds + microseconds * 1e-6);
}

void	ft_debug_parsing(t_parse *p)
{
	t_sph *aux = p->sp;
	t_pl *aux2 = p->pl;
	t_cy	*aux3 = p->cy;
	printf("A:	amlr: %f\t\tRGB: %i , %i , %i\n", p->am_ratio, p->am_color.r, p->am_color.g, p->am_color.b);
	printf("C:	cam_point: %f, %f, %f\t\t", p->cam->origin.x, p->cam->origin.y, p->cam->origin.z);
	printf("cam_nvec: %f, %f, %f\t\t", p->cam->fw.x, p->cam->fw.y, p->cam->fw.z);
	printf("cam_fov: %f\n", p->cam->fov / (PI / 180));
	printf("L:	light_vec: %f, %f, %f		light_ratio: %f\t\t light_color: %i , %i , %i\n", p->l_point.x, p->l_point.y, p->l_point.z, p->l_bright, p->l_color.r, p->l_color.g, p->l_color.b);
	printf("viewport data: center: (%f, %f, %f)\t\t lower_left: (%f, %f, %f)\n"
		, p->cam->center.x, p->cam->center.y, p->cam->center.z, p->cam->ll.x, p->cam->ll.y, p->cam->ll.z);
	printf("viewport data: vertical: (%f, %f, %f)\t\t horizontal: (%f, %f, %f)\n"
		, p->cam->ver.x, p->cam->ver.y, p->cam->ver.z, p->cam->hor.x, p->cam->hor.y, p->cam->hor.z);
	printf("vp_h: %f, vp_w: %f\n", p->cam->vp_h, p->cam->vp_w);
	int i = 0;
	while (aux)
	{
		printf("sp[%i]: sp_point: %f, %f, %f\t\t", i, aux->point.x, aux->point.y, aux->point.z);
		printf("diam: %f\t\t", aux->diam);
		printf("RGB: %i , %i , %i\n",  aux->color.r, aux->color.g, aux->color.b);
		i++;
		aux = aux->next;
	}
	i = 0;
	while (aux2)
	{
		printf("pl[%i]: pl_point: %f, %f, %f\t\t", i, aux2->point.x, aux2->point.y, aux2->point.z);
		printf("pl_n_vec: %f, %f, %f\t\t", aux2->n_vector.x, aux2->n_vector.y, aux2->n_vector.z);
		printf("RGB: %i , %i , %i\n",  aux2->color.r, aux2->color.g, aux2->color.b);
		i++;
		aux2 = aux2->next;
	}
	i = 0;
	while (aux3)
	{
		//printf("debug_cilindro\n");
		printf("cy[%i]: cy_point: %f, %f, %f\t\t", i, aux3->point.x, aux3->point.y, aux3->point.z);
		printf("cy_n_vec: %f, %f, %f\t\t", aux3->n_vector.x, aux3->n_vector.y, aux3->n_vector.z);
		printf("diam: %f\t\t", aux3->diam);
		printf("height: %f\t\t", aux3->height);
		printf("RGB: %i , %i , %i\n",  aux3->color.r, aux3->color.g, aux3->color.b);
		i++;
		aux3 = aux3->next;
	}
}
