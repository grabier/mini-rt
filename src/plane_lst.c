/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:12:34 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/25 18:40:13 by aehrl            ###   ########.fr       */
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

void	ft_free_pl(t_parse *p)
{
	t_pl	*aux;

	while (p->pl)
	{
		if (p->pl->diffuse)
			mlx_delete_image(p->data, p->pl->diffuse);
		aux = p->pl->next;
		//printf("freed a plane\n");
		free(p->pl);
		p->pl = aux;
	}
}

void	ft_pladd_back(t_pl **lst, t_pl *new)
{
	t_pl	*aux;

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

void	ft_pladd_front(t_pl **lst, t_pl *new)
{
	new->next = *lst;
	*lst = new;
}

t_pl	*ft_plnew(t_vec p, t_vec n, t_color c, t_parse *parse)
{
	t_pl	*new_node;

	new_node = (t_pl *)malloc(sizeof(t_pl));
	if (!new_node)
		return (NULL);
	new_node->color = c;
	new_node->point = p;
	new_node->n_vector = n;
	new_node->next = NULL;
	new_node->diffuse = mlx_new_image(parse->data, MAX_W, MAX_H);
	//printf("created a plane\n");
	return (new_node);
}

int	ft_plsize(t_pl *lst)
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