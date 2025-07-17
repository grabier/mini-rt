/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:02:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/17 17:34:26 by gmontoro         ###   ########.fr       */
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

void	ft_render_loop(t_parse *pr)
{

	int		j;
	int		i;
	t_ray	ray;
	//t_color	color;

	i = 0;
	j = 0;
	while (j < MAX_H)
	{
		i = 0;
		while (i < MAX_W)
		{
			ray = ft_calc_ray(i, j, pr);
			if (!ft_sp_intersection(ray, pr, i, j))
				mlx_put_pixel(pr->img, i, j, 0xFF000000);
			i++;
		}
		j++;
	}
	end_timer(pr->start);
	mlx_image_to_window(pr->data, pr->img, 0, 0);
	mlx_loop(pr->data);
}

int main(int argc, char **argv)
{
	//ft_draw_gradient();
	t_parse * program = ft_parsing(argc, argv);
	if (!program)
		return (1);
	//printf("up: \t");
	//printv(program->cam->up);
	//program->cam->up.y *= -1;
	ft_render_loop(program); 
	return (ft_free_parsing(program), 0);
}