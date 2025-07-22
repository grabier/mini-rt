/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:01:26 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/22 16:37:26 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_line(char *line, t_parse *program)
{
	char	**spline;

	spline = ft_split(line, '|');
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

char	*ft_format_line(char *str)
{
	char	*line;
	int		size;
	int		i;

	i = -1;
	size = ft_strlen(str) - ft_space_count(str) + ft_arg_count(str);
	line = malloc((size + 1) * sizeof(char));
	if (!line)
		return (printf("malloc error\n"), NULL);
	while (++i < size)
		line[i] = 'a';
	line[size] = '\0';
	line = ft_delete_spaces(str, line);
	//printf("new format %s\n", line);
	return (line);
}
t_parse	*ft_read_file(int fd)
{
	char	*line;
	char	*argument;
	t_parse	*program;

	program = ft_init_parse();
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (line[0] != '\n')
		{
			argument = ft_format_line(line);
			if (!ft_check_argument(argument))
				return (printf("Error\nFile parsing incorrect"),
				free(argument), free(line), ft_free_parsing(program));
			if (!ft_parse_line(argument, program))
				return (free(argument),  free(line), ft_free_parsing(program));
			free(argument);
		}
		free(line);
	}
	close(fd);
	return (program);
}

int		ft_check_extension(char *file) //can be added to parsing function
{
	int	i;

	i = ft_strlen(file);
	if (i < 3)
		return (0);
	if (file[i - 1] != 't' || file[i - 2] != 'r' || file[i - 3] != '.')
		return (0);
	return (1);
}

int	ft_check_parsing (t_parse *p)
{
	if (p->A > 1) // should be > 1 as we can start the scene without an ambient light
		return (printf("Error:Only one abient light allowed\n"), ft_free_parsing(p), 0);
	if (p->C == 0) 
		return (printf("Error: No camera\n"), ft_free_parsing(p), 0);
	if (p->C > 1) 
		return (printf("Error:Only one camera allowed\n"), ft_free_parsing(p), 0);
	if (p->L > 1) // multiple lights allowed in bonus
		return (printf("Error:Only one light allowed\n"), ft_free_parsing(p), 0);
	if (p->A == 0 && p->L == 0) // should be > 1 as we can start the scene without an ambient light
		return (printf("Error: No ambient lighting or light set\n"), ft_free_parsing(p), 0);
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
	return (close(fd), program);
}
