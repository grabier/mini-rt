/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:36:39 by gmontoro          #+#    #+#             */
/*   Updated: 2025/07/08 21:27:24 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
#include <math.h>

static int	skip_spaces_and_sign(const char *str, int *i, int *sign)
{
	int	index;

	index = 0;
	while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
		index++;
	if (str[index] == '-')
	{
		*sign = -1;
		index++;
	}
	else if (str[index] == '+')
		index++;
	*i = index;
	return (0);
}

static double	parse_integer_part(const char *str, int *i)
{
	double	result;
	int		index;

	result = 0.0f;
	index = *i;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10.0f + (str[index] - '0');
		index++;
	}
	*i = index;
	return (result);
}

static double	parse_fractional_part(const char *str, int *i)
{
	double	fraction;
	double	divisor;
	int		index;

	fraction = 0.0f;
	divisor = 10.0f;
	index = *i;
	while (str[index] >= '0' && str[index] <= '9')
	{
		fraction += (str[index] - '0') / divisor;
		divisor *= 10.0f;
		index++;
	}
	*i = index;
	return (fraction);
}

static double	apply_exponent(char *str, int *i, double result, int exp_sign)
{
	int		exponent;
	int		index;

	exponent = 0;
	index = *i;
	if (str[index] == 'e' || str[index] == 'E')
	{
		index++;
		if (str[index] == '-')
		{
			exp_sign = -1;
			index++;
		}
		else if (str[index] == '+')
			index++;
		while (str[index] >= '0' && str[index] <= '9')
		{
			exponent = exponent * 10 + (str[index] - '0');
			index++;
		}
		result *= powf(10.0f, exponent * exp_sign);
	}
	*i = index;
	return (result);
}

int	ft_double_check(char *str)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != '-')
			return ( 0);
		if ((str[i] == '.' && (!str[i + 1])) || (i == 0 && str[i] == '.'))
			return (0);
		if (str[i] == '.')
			cont++;
		i++;
	}
	if (cont > 1)
		return (0);
	return (1);
}

double	ft_atod(char *str)
{
	int		i;
	int		sign;
	double	result;
	double	fraction;

	i = 0;
	if (!ft_double_check(str))
		return (2.232323);
	sign = 1;
	skip_spaces_and_sign(str, &i, &sign);
	result = parse_integer_part(str, &i);
	fraction = 0.0f;
	if (str[i] == '.')
	{
		i++;
		fraction = parse_fractional_part(str, &i);
	}
	result += fraction;
	result = apply_exponent(str, &i, result, 1);
	return (result * sign);
}

/* #include <stdio.h>

int main(int argc, char **argv)
{
	float a = ft_atod(argv[1]);
	printf("result : %f\n", a);
	return (0);
} */
