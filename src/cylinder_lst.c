/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:05:16 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/29 18:46:22 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

/* void	ft_sphprint(t_sph *lst)
{
	while (lst)
	{
		printf("token: [%s]\t", lst->token);
		printf("type: [%i]\n", lst->type);
		lst = lst->next;
	}
} */

void	ft_free_cy(t_parse *p)
{
	t_cy	*aux;

	while (p->cy)
	{
		aux = p->cy->next;
		//printf("freed a cylinder\n");
		free(p->cy);
		p->cy = aux;
	}
}

void	ft_cyadd_back(t_cy **lst, t_cy *new)
{
	t_cy	*aux;
 
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

void	ft_cyadd_front(t_cy **lst, t_cy *new)
{
	new->next = *lst;
	*lst = new;
}

t_cy	*ft_cynew(t_aux	params)
{
	t_cy	*new_node;

	new_node = (t_cy *)malloc(sizeof(t_cy));
	if (!new_node)
		return (NULL);
	new_node->color = params.color;
	new_node->point = params.point;
	new_node->n_vector = params.n_vector;
	new_node->r = params.diam / 2;
	new_node->height = params.height;
	new_node->next = NULL;
	//printf("created a cylinder\n");
	return (new_node);
}

int	ft_cysize(t_cy *lst)
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
