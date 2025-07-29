/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:02:03 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/29 18:46:04 by aehrl            ###   ########.fr       */
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

t_parse	*ft_free_parsing(t_parse *p)
{
	if (p->sp != 0)
		ft_free_sp(p);
	if (p->pl != 0)
		ft_free_pl(p);
	if (p->cy != 0)
		ft_free_cy(p);
	if (p->cam)
		free(p->cam);
	if (p->hit)
		free(p->hit);
	free(p);
	return (NULL);
}