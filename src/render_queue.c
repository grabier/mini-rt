/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:32:47 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/29 16:48:42 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	free_render_queue(t_parse *pr)
{
	int			object_count;
	int			i;

	object_count = pr->sp_count + pr->pl_count + pr->cy_count;
	i = 0;
	while(i < object_count && pr->render_queue)
	{
		if (pr->render_queue[i])
		{
			mlx_delete_image(pr->data, pr->render_queue[i]->img);
			free(pr->render_queue[i]);
		}
		i++;
	}
	free(pr->render_queue);
}

int	fill_render_queue_spheres(t_parse *pr)
{
	int		i;
	t_sph	*aux;

	i = 0;
	aux = pr->sp;
	while (i < pr->sp_count)
	{
		pr->render_queue[i] = (t_render_queue *)malloc(sizeof(t_render_queue));
		pr->render_queue[i]->img = aux->diffuse;
		pr->render_queue[i]->distance = vlen(aux->point) - (aux->diam / 2);
		pr->render_queue[i]->point = aux->point;
		pr->render_queue[i]->diam = aux->diam;
		aux = aux->next;
		i++;
	}
	return(i);
}

int	fill_render_queue_cylinders(t_parse *pr, int i,  t_cy **lst)
{
	int		j;
	t_cy	*aux;

	j = 0;
	aux = *lst;
	while (aux != NULL && j < pr->cy_count)
	{
		pr->render_queue[i] = (t_render_queue *)malloc(sizeof(t_render_queue));
		pr->render_queue[i]->img = aux->diffuse;
		pr->render_queue[i]->distance = vlen(aux->point) - (aux->r / 2);
		pr->render_queue[i]->point = aux->point;
		pr->render_queue[i]->diam = aux->r;
		aux = aux->next;
		i++;
		j++;
	}
	return(i);
}

/* void	fill_render_queue(t_parse *pr, t_pl **lst)
{
	int	object_count;
	int i;
	t_pl	*aux;

	object_count = pr->sp_count + pr->pl_count + pr->cy_count;
	i = 0;
	i = fill_render_queue_spheres(pr, 0, &pr->sp);
	i += fill_render_queue_cylinders(pr, i, &pr->cy);
	aux = *lst;
	while(aux != NULL && i < object_count)
	{
	//	pr->render_queue[i]->img = aux->diffuse;
		pr->render_queue[i]->point = aux->point;
		pr->render_queue[i]->diam = 0;
		aux = aux->next;
		i++;
	}
} */
void	fill_render_queue(t_parse *pr)
{
	int	object_count;
	int i;
	t_pl	*aux;

	object_count = pr->sp_count + pr->pl_count + pr->cy_count;
	i = fill_render_queue_spheres(pr);
	i = fill_render_queue_cylinders(pr, i, &pr->cy); // could just be one function for all
	aux = pr->pl;
	while(aux != NULL && i < object_count)
	{
		pr->render_queue[i] = (t_render_queue *)malloc(sizeof(t_render_queue));
		pr->render_queue[i]->img = aux->diffuse;
		pr->render_queue[i]->distance = vlen(aux->point);
		pr->render_queue[i]->point = aux->point;
		pr->render_queue[i]->diam = 0;
		aux = aux->next;
		i++;
	}
}

void sort_render_queue(t_render_queue **queue, int size)
{
	t_render_queue	*aux;
	int i;
	double	dist_a;
	double	dist_b;

	i = 0;
	//(void)queue;
	while(i < size)
	{
		if (i + 1 != size)
		{
			//need to update calculation for planes and cylinders
			dist_a = queue[i]->distance; //does not take camera into account
			dist_b = queue[i + 1]->distance;
			printf("[%d]distance_a %f\n[%d]distance_b:%f\n\n",i, dist_a,i + 1,  dist_b);
			if (dist_a > dist_b && dist_b != 0)
			{
				aux = queue[i + 1];
				queue[i + 1] = queue[i];
				queue[i] = aux;
				i = 0;
			}
			else
				i++;
		}
		else
			i++;
	}
}

