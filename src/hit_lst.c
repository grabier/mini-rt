/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:39:01 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/22 17:00:34 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_free_hit(t_hit *p)
{
	t_hit	*aux;

	while (p)
	{
		aux = p->next;
		//printf("freed a hitere\n");
		free(p);
		p = aux;
	}
}

void	ft_hitadd_back(t_hit **lst, t_hit *new)
{
	t_hit	*aux;

	aux = *lst;
	if (!new)
		return ;
	if (!aux)
	{
		*lst = new;
		return ;
	}
	while (aux->next)
		aux = aux->next;
	aux->next = new;
}

void	print_hit_list(t_hit *hit_lst)
{
	t_hit	*aux;

	aux = hit_lst;
	while (aux)
	{
		printf("hit_point\t");
		printv(aux->colission);
		printf("color\t");
		ft_printcolor(aux->pixel_color);
		aux = aux->next;
	}
	printf("\n");
}

void	ft_hitadd_front(t_hit **lst, t_hit *new)
{
	new->next = *lst;
	*lst = new;
}

t_hit	*ft_hitnew(t_vec hit, t_color color, t_vec n, int m)
{
	t_hit	*new_node;

	new_node = (t_hit *)malloc(sizeof(t_hit));
	if (!new_node)
		return (NULL);	
	new_node->colission = hit;
	new_node->pixel_color = color;
	new_node->object = m;
	new_node->normal = n;
	new_node->next = NULL;
	//printf("created a hitere\n");
	return (new_node);
}

int	ft_hitsize(t_hit *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
