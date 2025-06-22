/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:02:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/06/22 15:42:18 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

# define MAX_W 3840  //3840
# define MAX_H 2160  //2160

/* uint32_t	rgb_to_hex_alpha(t_color color)
{
	return (color.b << 24) | (color.g << 16) |
			(color.r << 8) | 0xFF;
}

void ft_draw_gradient()
{
	mlx_t	*data;
	mlx_image_t	*img;
	t_color color;

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

			color.r = (int)(255.999 * r);
			color.g = (int)(255.999 * g);
			color.b = (int)(255.999 * b);
			mlx_put_pixel(img, j, i, rgb_to_hex_alpha(color));
		}
	}

	mlx_image_to_window(data, img, 0, 0);
	mlx_loop(data);
} */

void	ft_debug_parsing(t_parse *p)
{
	printf("A:	amlr: %f\t\tRGB: %i , %i , %i\n", p->am_ratio, p->am_color.r, p->am_color.g, p->am_color.b);
	printf("C:	cam_point: %f, %f, %f\t\t", p->cam_point.x, p->cam_point.y, p->cam_point.z);
	printf("cam_nvec: %f, %f, %f\t\t", p->cam_vector.x, p->cam_vector.y, p->cam_vector.z);
	printf("cam_fov: %i\n", p->cam_fov);
	printf("L:	light_point: %f, %f, %f		light_ratio: %f\t\t light_color: %i , %i , %i\n", p->l_point.x, p->l_point.y, p->l_point.z, p->l_bright, p->l_color.r, p->l_color.g, p->l_color.b);
}

int main(int argc, char **argv)
{
	//ft_draw_gradient();
	t_parse * program = ft_parsing(argc, argv);
	if (!program)
		return (1);
	ft_debug_parsing(program);
	free(program);
	return (0);
}