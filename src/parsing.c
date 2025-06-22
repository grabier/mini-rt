/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:01:26 by gmontoro          #+#    #+#             */
/*   Updated: 2025/06/22 14:05:35 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_line(char *line, t_parse *program)
{
	char	**spline;

	spline = ft_split(line, ' ');
	//printf("compare: %s\n", spline[0]);
	if (!ft_strcmp(spline[0], "A"))
		return (ft_parse_ambient(spline, program));
	else if (!ft_strcmp(spline[0], "C"))
		return (ft_parse_camera(spline, program));
	else if (ft_strcmp(spline[0], "L"))
		return (ft_parse_light(spline, program));
	/*else if (ft_strcmp(spline[0], "s"))
		return (ft_free(spline), ft_parse_sphere(spline, program));
	else if (ft_strcmp(spline[0], "p"))
		return (ft_free(spline), ft_parse_plane(spline, program));
	else if (ft_strcmp(spline[0], "cy"))
		return (ft_free(spline), ft_parse_cylinder(spline, program)); */
	else if (ft_strcmp(spline[0], "\n"))
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
	parse->s = 0;
	parse->p = 0;
	parse->cy = 0;
	return (parse);
}

t_parse	*ft_read_file(int fd)
{
	char	*line;
	t_parse	*program;

	program = malloc(sizeof(t_parse));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!ft_parse_line(line, program))
			return (free(program), free(line), NULL);
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
	if (!program)
		return (NULL);
	return (program);
}
