/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:01:26 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/09 19:47:21 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_line(char *line, t_parse *program)
{
	char	**spline;

	spline = ft_split(line, ' ');
	/* if (spline[0][0] == '\0')
		printf("entra al salto: %s\n", spline[0]);
	printf("entra al parse: %s\n", spline[0]); */
	/* if (spline[0][1] != '\0'){
		printf("sp[0]: %s\n", spline[0]);
		printf("sp[1]: %s\n", spline[1]);
		printf("sp[2]: %s\n", spline[2]);
	} */
	if (!ft_strcmp(spline[0], "A"))
		return (ft_parse_ambient(spline, program));
	else if (!ft_strcmp(spline[0], "C"))
		return (ft_parse_camera(spline, program));
	else if (!ft_strcmp(spline[0], "L"))
		return (ft_parse_light(spline, program));
	else if (!ft_strcmp(spline[0], "sp"))
		return (ft_parse_sphere(spline, program));
	else if (!ft_strcmp(spline[0], "pl"))
		return (ft_parse_plane(spline, program));
	else if (!ft_strcmp(spline[0], "cy"))
		return (ft_parse_cylinder(spline, program));
	else if (!ft_strcmp(line, "\n"))
		return (ft_free(spline), 1);
	else
		return (ft_free(spline), 0);
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
	parse->data = mlx_init(MAX_W, MAX_H, "Hello world!", 1);
	parse->img = mlx_new_image(parse->data, MAX_W, MAX_H);
	return (parse);
}

t_parse	*ft_read_file(int fd)
{
	char	*line;
	t_parse	*program;

	program = ft_init_parse();
	while (1)
	{
		line = get_next_line(fd);
		/* if (!ft_strcmp(line, "\n"))
			printf("salotlinea\n");
		else
			printf("NO salotlinea\n"); */
		if (!line)
			break;
		if (!ft_parse_line(line, program))
			return (free(line), ft_free_parsing(program));
		free(line);
	}
	close(fd);
	return (program);
}

int		ft_check_extension(char *file)
{
	int	i;

	i = ft_strlen(file);
	//printf("filename: %s, finalletter: %c\n", file, file[i -1 ]);
	if (file[i - 1] != 't' || file[i - 2] != 'r' || file[i - 3] != '.')
		return (0);
	return (1);
}


t_parse	*ft_free_parsing(t_parse *p)
{
	ft_free_sp(p);
	ft_free_pl(p);
	ft_free_cy(p);
	free(p->cam);
	free(p);
	return (NULL);
}

int	ft_check_parsing (t_parse *p)
{
	if (p->A != 1)
		return (printf("Error: No ambient lighting\n"), ft_free_parsing(p), 0);
	//printf("cameras: %i\n", p->C);
	if (p->C != 1)
		return (printf("Error: No camera\n"), ft_free_parsing(p), 0);
	if (p->L != 1)
		return (printf("Error: No light\n"), ft_free_parsing(p), 0);
	if (p->pl_count == 0 && p->cy_count == 0 && p->sp_count == 0)
		return (printf("Error: No object to represent\n"), ft_free_parsing(p), 0);
	return (1);
}

t_parse	*ft_parsing(int argc, char **argv)
{
	t_parse	*program;
	int		fd;

	if (argc != 2)
		return (printf("Error: invalid amount of arguments\n"), NULL);
	if (!ft_check_extension(argv[1]))
		return (printf("Error: invalid file type\n"), NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error: couldn't open file\n"), NULL);
	program = ft_read_file(fd);
	if (!program || !ft_check_parsing(program))
		return (NULL);
	return (program);
}
