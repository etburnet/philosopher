/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:13:46 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/21 16:43:25 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	ft_isdigit(char n)
{
	if (n >= '0' && n <= '9')
		return (1);
	return (0);
}

int	ft_is_live(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_live);
	if (philo->data->live == 1)
		return (pthread_mutex_unlock(&philo->data->m_live), 1);
	else
		return (pthread_mutex_unlock(&philo->data->m_live), 0);
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
