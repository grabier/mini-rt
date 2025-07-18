/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:08:02 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/18 19:24:12 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec ft_init_vec(double x, double y, double z)
{
	t_vec p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_color ft_init_color(char **sp)
{
	int	a;
	int	b;
	int	c;
	t_color color;

	a = ft_atoi(sp[0]);
	b = ft_atoi(sp[1]);
	c = ft_atoi(sp[2]);
	color.r = a;
	color.g = b;
	color.b = c;
	return (color);
}

t_parse *ft_init_parse()
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	parse->A = 0;
	parse->C = 0;
	parse->L = 0;
	parse->sp_count = 0;
	parse->pl_count = 0;
	parse->cy_count = 0;
	parse->sp = NULL;
	parse->pl = NULL;
	parse->cy = NULL;
	parse->cam = NULL;
	parse->render_queue = NULL;
	parse->data = mlx_init(MAX_W, MAX_H, "Hello world!", 1);
	//parse->img = mlx_new_image(parse->data, MAX_W, MAX_H);
	return (parse);
}

t_render_queue	**init_render_queue(t_parse *program)
{
	int			object_count;
	t_render_queue **queue;

	printf("sphere count: %d\nplane count: %d\ncylinder count: %d\n", program->sp_count, program->pl_count, program->cy_count);
	object_count = program->sp_count + program->pl_count + program->cy_count;
	//queue = (t_render_queue **)malloc(object_count * sizeof(t_render_queue *));
	queue = (t_render_queue **)malloc(program->sp_count * sizeof(t_render_queue *));//just for testing spheres
	if (!queue)
		return (NULL);
	printf("render queue initialisation success\nrender queue size:%d\n", object_count);
	return(queue);
}