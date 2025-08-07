/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:02:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/08/07 17:24:19 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double rocket(t_vec p);

uint32_t	rgb_to_hex_alpha(t_color color)
{
	return ((color.r << 24) | (color.g << 16) |
		(color.b << 8) | 255);
}

void	ft_render_loop(t_parse *pr)
{
	int		j;
	int		i;

	j = 0;
	start_timer(&pr->start);
	while (j < MAX_H)
	{
		i = 0;
		while (i < MAX_W)
		{
			mlx_put_pixel(pr->img, i, j, render(pr, i, j));
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
	t_parse	*program = ft_parsing(argc, argv);
	printf("camera.or\n");
	printv(program->cam->fw);
	if (!program)
		return (1);
	//printv(program->cam->up);
	//program->cam->up.y *= -1;
	ft_render_loop(program);
	return (ft_free_parsing(program), 0);
}