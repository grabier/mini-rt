/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:02:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/02 18:23:28 by gmontoro         ###   ########.fr       */
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
	t_sph *aux = p->sp;
	t_pl *aux2 = p->pl;
	t_cy	*aux3 = p->cy;
	printf("A:	amlr: %f\t\tRGB: %i , %i , %i\n", p->am_ratio, p->am_color.r, p->am_color.g, p->am_color.b);
	printf("C:	cam_point: %f, %f, %f\t\t", p->cam_point.x, p->cam_point.y, p->cam_point.z);
	printf("cam_nvec: %f, %f, %f\t\t", p->cam_vector.x, p->cam_vector.y, p->cam_vector.z);
	printf("cam_fov: %i\n", p->cam_fov);
	printf("L:	light_point: %f, %f, %f		light_ratio: %f\t\t light_color: %i , %i , %i\n", p->l_point.x, p->l_point.y, p->l_point.z, p->l_bright, p->l_color.r, p->l_color.g, p->l_color.b);
	int i = 0;
	while (aux)
	{
		printf("sp[%i]: sp_point: %f, %f, %f\t\t", i, aux->point.x, aux->point.y, aux->point.z);
		printf("diam: %f\t\t", aux->diam);
		printf("RGB: %i , %i , %i\n",  aux->color.r, aux->color.g, aux->color.b);
		i++;
		aux = aux->next;
	}
	i = 0;
	while (aux2)
	{
		printf("pl[%i]: pl_point: %f, %f, %f\t\t", i, aux2->point.x, aux2->point.y, aux2->point.z);
		printf("pl_n_vec: %f, %f, %f\t\t", aux2->n_vector.x, aux2->n_vector.y, aux2->n_vector.z);
		printf("RGB: %i , %i , %i\n",  aux2->color.r, aux2->color.g, aux2->color.b);
		i++;
		aux2 = aux2->next;
	}
	i = 0;
	while (aux3)
	{
		//printf("debug_cilindro\n");
		printf("cy[%i]: cy_point: %f, %f, %f\t\t", i, aux3->point.x, aux3->point.y, aux3->point.z);
		printf("cy_n_vec: %f, %f, %f\t\t", aux3->n_vector.x, aux3->n_vector.y, aux3->n_vector.z);
		printf("diam: %f\t\t", aux3->diam);
		printf("height: %f\t\t", aux3->height);
		printf("RGB: %i , %i , %i\n",  aux3->color.r, aux3->color.g, aux3->color.b);
		i++;
		aux3 = aux3->next;
	}
}

int main(int argc, char **argv)
{
	//ft_draw_gradient();
	t_parse * program = ft_parsing(argc, argv);
	if (!program)
		return (1);
	ft_debug_parsing(program);
	/* ft_free_sp(program);
	ft_free_pl(program);
	ft_free_cy(program);
	free(program); */
	return (ft_free_parsing(program), 0);
}