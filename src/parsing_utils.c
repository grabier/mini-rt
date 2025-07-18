/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:11:45 by aehrl             #+#    #+#             */
/*   Updated: 2025/07/18 19:12:01 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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
	if (c == 'A' && arg_count != 2) // L should be 2 for mandotory
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