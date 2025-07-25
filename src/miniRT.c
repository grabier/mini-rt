/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:02:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/25 18:43:08 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

uint32_t	rgb_to_hex_alpha(t_color color)
{
	return ((color.r << 24) | (color.g << 16) |
		(color.b << 8) | 255);
}

/* uint32_t	rgb_to_hex_alpha(t_color color)
{
	return (color.r << 24) | (color.g << 16) |
			(color.b << 8) | 255;
} */

/* void ft_draw_gradient()
{
	mlx_t	*data;
	mlx_image_t	*img;
	t_color color;
	color.r = (int)(135);
	color.g = (int)(206);
	color.b = (int)(235);	
	data = mlx_init(MAX_W, MAX_H, "Hello world!", 1);
	img = mlx_new_image(data, MAX_W, MAX_H);
	if (!data || !img){
		printf("problemo\n");
		return ;
	}
	for(int j = 0; j < MAX_W; j++){
		for (int i = 0; i < MAX_H; i++){
			double r = (double)(j) / (MAX_W - 1);
			double g = (double)(i) / (MAX_H - 1);
			double b = 0.0;
			mlx_put_pixel(img, j, i, rgb_to_hex_alpha(color));
		}
	}
	mlx_image_to_window(data, img, 0, 0);
	mlx_loop(data);
} */
void	ft_create_images(t_parse *pr)
{

	int		j;
	int		i;
	t_ray	ray;

	i = 0;
	j = 0;
	start_timer(&pr->start);
	while (j < MAX_H)
	{
		i = 0;
		while (i < MAX_W)
		{
			ray = ft_calc_ray(i, j, pr);
			ft_colission(ray, pr, i, j);
			i++;
		}
		j++;
	}
	end_timer(pr->start);
	//mlx_image_to_window(pr->data, pr->img, 0, 0);
	//mlx_loop(pr->data);
}

/*  void	create_sphere_image_normals(t_parse *pr)
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
} */
 void draw_render_queue(t_parse *pr)
{
/* 	int	i;

	i = pr->sp_count + pr->cy_count + pr->pl_count - 1; // will be updated to total number of objects
	printf("RENDER QUEUE SIZE %d\n", i);
	while (i >= 0)
	{
		printf("ENTER\n");
		mlx_image_to_window(pr->data, pr->render_queue[i]->img, 0, 0);
		i--;
	} */
	mlx_image_to_window(pr->data, pr->img, 0, 0);
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

	draw_render_queue(pr);
	//mlx_resize_hook(mlx_t* mlx, mlx_resizefunc func, void* param);
	//mlx_resize_hook(pr->data, &mlx_update_matrix, pr->data);
	mlx_key_hook(pr->data, &esc_keyhook, pr->data); //handle ESC
	mlx_loop(pr->data);
	
}

int main(int argc, char **argv)
{
	//ft_draw_gradient();
	t_parse	*program = ft_parsing(argc, argv);
	if (!program)
		return (1);
	ft_create_images(program);
	program->render_queue = init_render_queue(program);
	if (program->render_queue == NULL)
		return (ft_free_parsing(program), 0);//printv(program->cam->up);
	fill_render_queue(program); //
	ft_render_loop(program);
	mlx_terminate(program->data);
	return (ft_free_parsing(program), 0);
}