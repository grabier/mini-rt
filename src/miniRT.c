/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:02:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/11 20:36:10 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

uint32_t	rgb_to_hex_alpha(t_color color)
{
	return (color.b << 24) | (color.g << 16) |
		   (color.r << 8) | 255;
}

/* uint32_t	rgb_to_hex_alpha(t_color color)
{
	return (color.r << 24) | (color.g << 16) |
			(color.b << 8) | 255;
} */

void ft_draw_gradient()
{
	mlx_t	*data;
	mlx_image_t	*img;
	t_color color;
	/* color.r = (int)(135);
	color.g = (int)(206);
	color.b = (int)(235);	 */
	data = mlx_init(MAX_W, MAX_H, "Hello world!", 1);
	img = mlx_new_image(data, MAX_W, MAX_H);
	if (!data || !img){
		printf("problemo\n");
		return ;
	}
	for(int j = 0; j < MAX_W; j++){
		for (int i = 0; i < MAX_H; i++){
			/* double r = (double)(j) / (MAX_W - 1);
			double g = (double)(i) / (MAX_H - 1);
			double b = 0.0; */

			
			mlx_put_pixel(img, j, i, rgb_to_hex_alpha(color));
		}
	}
	mlx_image_to_window(data, img, 0, 0);
	mlx_loop(data);
}

void	ft_debug_parsing(t_parse *p)
{
	t_sph *aux = p->sp;
	t_pl *aux2 = p->pl;
	t_cy	*aux3 = p->cy;
	printf("A:	amlr: %f\t\tRGB: %i , %i , %i\n", p->am_ratio, p->am_color.r, p->am_color.g, p->am_color.b);
	printf("C:	cam_point: %f, %f, %f\t\t", p->cam->origin.x, p->cam->origin.y, p->cam->origin.z);
	printf("cam_nvec: %f, %f, %f\t\t", p->cam->fw.x, p->cam->fw.y, p->cam->fw.z);
	printf("cam_fov: %f\n", p->cam->fov / (PI / 180));
	printf("L:	light_vec: %f, %f, %f		light_ratio: %f\t\t light_color: %i , %i , %i\n", p->l_point.x, p->l_point.y, p->l_point.z, p->l_bright, p->l_color.r, p->l_color.g, p->l_color.b);
	printf("viewport data: center: (%f, %f, %f)\t\t lower_left: (%f, %f, %f)\n"
		, p->cam->center.x, p->cam->center.y, p->cam->center.z, p->cam->ll.x, p->cam->ll.y, p->cam->ll.z);
	printf("viewport data: vertical: (%f, %f, %f)\t\t horizontal: (%f, %f, %f)\n"
		, p->cam->ver.x, p->cam->ver.y, p->cam->ver.z, p->cam->hor.x, p->cam->hor.y, p->cam->hor.z);
	printf("vp_h: %f, vp_w: %f\n", p->cam->vp_h, p->cam->vp_w);
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

void	ft_print_sp_pixel(t_parse *p, t_sph *sp, int i, int j)
{
	/* if (i == 800 && j == 600){
		printf("DETECTAMOS HIT\n");
		printf("color: %X\n", rgb_to_hex_alpha(sp->color));
	}
	(void)p; */
	mlx_put_pixel(p->img, j, i, rgb_to_hex_alpha(sp->color));
}

mlx_image_t	*create_image_shadow(t_parse *pr)
{
	int		j;
	int		i;
	t_ray	ray;
	//t_color	color;

	i = 200;
	j = 400;
	while (j < MAX_H)
	{
		i = 0;
		while (i < MAX_W)
		{
			ray = ft_calc_ray(i, j, pr);
			if (ft_sp_intersection(ray, pr))
			{
				mlx_put_pixel(pr->img, i, j, 0xffff000a);
			}
			/*  else
			{
				mlx_put_pixel(pr->img, i, j, 0xFF87CEEB);
			} */
			i++;
		}
		j++;
	}
	return (pr->img);
}

mlx_image_t	*create_image_normals(t_parse *pr)
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
			if (ft_sp_intersection_vector(ray, pr))
				mlx_put_pixel(pr->img, i, j, rgb_to_hex_alpha(pr->sp->pixel_color));
			i++;
		}
		j++;
	}
	return (pr->img);
}

mlx_image_t	*create_image_color(t_parse *pr)
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
			if (ft_sp_intersection(ray, pr))
			{
				mlx_put_pixel(pr->img, i, j, rgb_to_hex_alpha(pr->sp->color));
			}
			/*  else
			{
				mlx_put_pixel(pr->img, i, j, 0xFF87CEEB);
			} */
			i++;
		}
		j++;
	}
	return (pr->img);
}

void	ft_render_loop(t_parse *pr, mlx_image_t *color, mlx_image_t *normals)
{

	
	mlx_image_to_window(pr->data, color, 0, 0);
	mlx_image_to_window(pr->data, normals, 0, 0);
	//mlx_image_to_window(pr->data, shadows, 0, 0);
	//shadows->enabled = false;
	mlx_loop(pr->data);
}

int main(int argc, char **argv)
{
	mlx_image_t *color;
	mlx_image_t *normals;
	//mlx_image_t *shadows;
	//ft_draw_gradient();
	t_parse * program = ft_parsing(argc, argv);
	if (!program)
		return (1);
	color = create_image_color(program);
	normals = create_image_normals(program);
	//shadows = create_image_shadow(program);
	//ft_debug_parsing(program);
	ft_render_loop(program, color, normals); 
	/* t_vec or = ft_init_vec(0, 0, 0);
	t_vec dir = ft_init_vec(0, 0, -1);
	t_ray ray;
	ray.dir = dir;
	ray.or = or; 
	ft_intersects_sp(ray, program->sp);
	printf("colision en : %f, %f, %f\n", 
					program->sp->colission.x, program->sp->colission.y, program->sp->colission.z);
	printf("determinante: %f\n", ft_calc_det(ray, program->sp)); 
	 ft_free_sp(program);
	ft_free_pl(program);
	ft_free_cy(program);
	free(program); */
	return (ft_free_parsing(program), 0);
}