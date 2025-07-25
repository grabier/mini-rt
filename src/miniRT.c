/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:02:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/18 20:03:05 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

uint32_t	rgb_to_hex_alpha(t_color color)
{
	return (color.r << 24) | (color.g << 16) |
		   (color.b << 8) | 255;
}

void	create_sphere_image_normals(t_parse *pr)
{
	int		j;
	int		i;
	t_ray	ray;

	i = 0;
	j = 0;
	while (j < MAX_H)
	{
		i = 0;
		while (i < MAX_W)
		{
			ray = ft_calc_ray(i, j, pr);
			ft_sp_intersection(ray, pr, i, j);
			i++;
		}
		j++;
	}
}

void display_sp_normals(t_parse *pr) // no longer need this function (handled by draw_render_queue)
{
	int	i;
	t_sph	*aux;

	i = 0;
	aux = pr->sp;
	while (i < pr->sp_count)
	{
		mlx_image_to_window(pr->data, aux->diffuse, 0, 0);
		aux = aux->next;
		i++;
	}
}
void draw_render_queue(t_parse *pr)
{
	int	i;

	i = pr->sp_count - 1; // will be updated to total number of objects
	while (i >= 0)
	{
		mlx_image_to_window(pr->data, pr->render_queue[i]->img, 0, 0);
		i--;
	}
}
void esc_keyhook(mlx_key_data_t keydata, void* param)
{
	mlx_t *mlx;
	
	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

void	ft_render_loop(t_parse *pr)
{
	//draw ambient light (should be bg color)
	draw_render_queue(pr);
	//mlx_resize_hook(mlx_t* mlx, mlx_resizefunc func, void* param);
	//mlx_resize_hook(pr->data, &mlx_update_matrix, pr->data);
	mlx_key_hook(pr->data, &esc_keyhook, pr->data); //handle ESC
	//if (pr->data)
	mlx_loop(pr->data);
	mlx_terminate(pr->data);
}

int main(int argc, char **argv)
{
	t_parse * program = ft_parsing(argc, argv);
	//int	size;

	if (!program)
		return (1);
	create_sphere_image_normals(program);
	//ft_debug_parsing(program);
	program->render_queue = init_render_queue(program);
	if (program->render_queue == NULL)
		return (ft_free_parsing(program), 0);
	fill_render_queue(program);
	//size = program->sp_count + program->pl_count + program->cy_count;
	//sort_render_queue(program->render_queue, size);
	sort_render_queue(program->render_queue, program->sp_count);
	ft_render_loop(program); 
	return (ft_free_parsing(program), 0);
}