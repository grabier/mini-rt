/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:08:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/25 18:39:59 by aehrl            ###   ########.fr       */
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

void	ft_free_sp(t_parse *p)
{
	t_sph	*aux;

	while (p->sp)
	{
		aux = p->sp->next;
		if (p->sp->diffuse)
			mlx_delete_image(p->data, p->sp->diffuse);
		//printf("freed a sphere\n");
		free(p->sp);
		p->sp = aux;
	}
}

void	ft_sphadd_back(t_sph **lst, t_sph *new)
{
	t_sph	*aux;

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

void	ft_sphadd_front(t_sph **lst, t_sph *new)
{
	new->next = *lst;
	*lst = new;
}

t_sph	*ft_sphnew(t_vec p, double d, t_color c, t_parse *parse)
{
	t_sph	*new_node;

	new_node = (t_sph *)malloc(sizeof(t_sph));
	if (!new_node)
		return (NULL);
	new_node->color = c;
	new_node->point = p;
	new_node->diam = d;
	new_node->in = 0;
	new_node->next = NULL;
	new_node->diffuse = mlx_new_image(parse->data, MAX_W, MAX_H);
	//printf("created a sphere\n");
	return (new_node);
}

int	ft_sphsize(t_sph *lst)
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