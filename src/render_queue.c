/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:32:47 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/18 19:56:23 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	free_render_queue(t_parse *pr)
{
	int			object_count;
	int			i;

	//object_count = pr->sp_count + pr->pl_count + pr->cy_count;
	object_count = pr->sp_count;
	i = 0;
	while(i < object_count)
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

int	fill_render_queue_spheres(t_parse *pr, int i, t_sph **lst)
{
	int		j;
	t_sph	*aux;

	j = 1;
	aux = *lst;
	while (j < pr->sp_count)
	{
		//pr->render_queue[i]->img = aux->diffuse;
		pr->render_queue[i]->point = aux->point;
		pr->render_queue[i]->diam = aux->diam;
		aux = aux->next;
		i++;
		j++;
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
		//pr->render_queue[i]->img = aux->diffuse;
		pr->render_queue[i]->point = aux->point;
		pr->render_queue[i]->diam = aux->diam;
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
	t_sph	*aux;

	object_count = pr->sp_count;
	i = 0;
	//i = fill_render_queue_spheres(pr, 0, &pr->sp);
	//i += fill_render_queue_cylinders(pr, i, &pr->cy);
	aux = pr->sp;
	while(aux != NULL && i < object_count)
	{
		
		pr->render_queue[i] = (t_render_queue *)malloc(sizeof(t_render_queue));
		pr->render_queue[i]->img = aux->diffuse;
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
	(void)queue;
	while(i < size)
	{
		if (i + 1 != size)
		{
			dist_a = vlen(queue[i]->point) - (queue[i]->diam / 2); //does not take camera into account
			dist_b = vlen(queue[i + 1]->point) - (queue[i + 1]->diam / 2); //does not take camera into account
			printf("[%d]distance_a %f\n[%d]distance_b:%f\n\n",i, dist_a,i + 1,  dist_b);
			if (dist_a > dist_b && dist_b != 0) //0 check for if we are inside the opbject (needs to be checked wiht updated calculation)
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

