/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:01:26 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/18 18:50:02 by aehrl            ###   ########.fr       */
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

int	ft_arg_count(char *str)
{
	int i;
	int	check;
	int arg_count;
	
	i = 0;
	check = 0;
	arg_count = 0;
	while(str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			check = 0;
		else if (check == 0)
		{
			arg_count++;
			check = 1;
		}
		i++;
	}
	return (arg_count);
}
int	ft_space_count(char *str)
{
	int i;
	int space_count;
	
	i = 0;
	space_count = 0;
	while(str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			space_count++;
		i++;
	}
	return (space_count);
}
char	*ft_delete_spaces(char *str, char *dst)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(str[i] != '\0' && dst[j])
	{
		
		if(str[i] == ' ' || str[i] == '\t')
			i++;
		else
		{
			if (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
				dst[j++] = '|';
			dst[j++] = str[i++];
		}
		if (str[i] == '\n')
		{
			str[i] = '\0';
			i++;
		}
	}
	dst[j] = '\0';
	return (dst);
}

int	ft_check_arg_count(char *str, int arg_count)
{
	int		i;
	char	c;
	i = 1;
	c = str[0];
	if ((c == 's' && str[1] != 'p') || (c == 'p' && str[1] != 'l')
		|| (c == 'c' && str[1] != 'y'))
		return (0);
	if (c == 's'|| c == 'p' || c == 'c')
		i++;
	while(str[i] != '\0')
	{
		if(!ft_isdigit(str[i]) && str[i] != ',' && str[i] != '.'
			&& str[i] != '-' && str[i] != '|' )
			return (0);
		i++;
	}
	if (c == 'A' && arg_count != 2)
		return (0);
	if ((c == 'C' ||  c == 'L'  ||  c == 's' ||  c == 'p' )
		&& arg_count != 3)
		return (0);
	if (c == 'c' && arg_count != 5)
		return (0);
	return (1);
}

int	ft_check_argument(char *str)
{
	int 	i;
	int		arg_count;
	char	c;
	
	i = 0;
	arg_count = 0;
	c = str[0];
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			arg_count++;
		else if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != '.'
			&& str[i] != '-' && str[i] != 'A' && str[i] != 'C'
			&& str[i] != 'L' && str[i] != 's' && str[i] != 'p'
			&& str[i] != 'l' && str[i] != 'c' && str[i] != 'y')
			return (0);
		if((c == 'A' || c == 'C' || c == 'L') && i > 0 && !ft_isdigit(str[i])
			&& str[i] != ',' && str[i] != '.' && str[i] != '-' && str[i] != '|')
			return (0);
		i++;
	}
	if (arg_count < 2 || arg_count > 5 || !ft_check_arg_count(str, arg_count))
		return (0);
	return (1);
}

char	*ft_format_line(char *str)
{
	char	*line;
	int		size;

	size = ft_strlen(str) - ft_space_count(str) + ft_arg_count(str);
	line = malloc((size + 1) * sizeof(char));
	if (!line)
		return (printf("malloc error\n"), NULL);
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
	if (p->sp != 0)
		ft_free_sp(p);
	if (p->pl != 0)
		ft_free_pl(p);
	if (p->cy != 0)
		ft_free_cy(p);
	if (p->cam)
		free(p->cam);
	if (p->render_queue)
		free_render_queue(p);
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
