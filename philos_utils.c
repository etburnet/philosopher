/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:13:46 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/19 14:42:48 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	ft_isdigit(char n)
{
	if (n >= '0' && n <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	isnegative;
	int	result;

	i = 0;
	isnegative = 1;
	result = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_isdigit(str[i]) && str[i] != '\0' && str[i] != '+')
		return (-1);
	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			isnegative *= -1;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - 48);
	return (result * isnegative);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		slen;
	char	*str;
	char	*cpy;

	str = (char *)s;
	slen = ft_strlen(str);
	cpy = (char *)malloc(slen + 1);
	i = 0;
	if (cpy == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static int	ft_count_digits(int n)
{
	int	count;

	count = 1;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;

	size = ft_count_digits(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	else if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[--size] = '0' + n % 10;
		n = n / 10;
	}
	return (str);
}
