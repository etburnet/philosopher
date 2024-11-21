/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:05:51 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/21 18:00:25 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 && *s1 == *s2 && i < n - 1)
	{
		s1++;
		s2++;
		i++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_int_check(char *str)
{
	char	*long_max_str;

	long_max_str = "2147483647";
	if (ft_strlen(str) > ft_strlen(long_max_str))
		return (1);
	else if (ft_strlen(str) == ft_strlen(long_max_str) && ft_strncmp(str,
			long_max_str, ft_strlen(str)) > 0)
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
	if (ft_int_check(str) == 1)
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

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long time, t_philo *philo)
{
	long long	start;

	start = ft_get_time();
	if (time <= 0)
		return ;
	while (1)
	{
		if (ft_is_live(philo) == 0)
			break ;
		if ((ft_get_time() - start) >= time)
			break ;
		usleep(1000);
	}
}
