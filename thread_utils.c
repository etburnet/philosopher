/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:34:20 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/21 18:00:49 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
}

int	ft_think(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->m_writing);
	time = ft_get_time();
	if (ft_log(philo, time, " is thinking") == 3)
		return (3);
	ft_usleep(philo->data->t_think, philo);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->m_writing);
	time = ft_get_time();
	if (ft_log(philo, time, " is sleeping") == 3)
		return (3);
	ft_usleep(philo->data->t_sleep, philo);
	return (0);
}

int	ft_log(t_philo *philo, long long time, char *str)
{
	int	ms;

	if (ft_is_live(philo) == 0)
		return (pthread_mutex_unlock(&philo->data->m_writing), 1);
	ms = time - philo->data->t_start;
	printf("%d %d %s\n", ms, philo->id, str);
	pthread_mutex_unlock(&philo->data->m_writing);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
