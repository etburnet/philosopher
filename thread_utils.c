/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:34:20 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/20 12:05:17 by eburnet          ###   ########.fr       */
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
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (ft_log(philo, time, " is thinking\n") == 3)
		return (3);
	if (usleep(philo->data->t_think * 1000) == -1)
		return (3);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (ft_log(philo, time, " is sleeping\n") == 3)
		return (3);
	if (usleep(philo->data->t_sleep * 1000) == -1)
		return (3);
	return (0);
}

int	ft_log(t_philo *philo, struct timeval time, char *str)
{
	char	*itoa;

	pthread_mutex_lock(&philo->data->m_writing);
	pthread_mutex_lock(&philo->data->m_live);
	if (philo->data->live == 0)
		return (pthread_mutex_unlock(&philo->data->m_live),
			pthread_mutex_unlock(&philo->data->m_writing), 1);
	pthread_mutex_unlock(&philo->data->m_live);
	itoa = ft_itoa((time.tv_sec * 1000 + time.tv_usec / 1000)
			- philo->data->t_start);
	if (itoa == NULL)
		return (3);
	ft_putstr_fd(itoa, 1);
	ft_putstr_fd(" ", 1);
	free(itoa);
	itoa = ft_itoa(philo->id);
	if (itoa == NULL)
		return (3);
	ft_putstr_fd(itoa, 1);
	free(itoa);
	ft_putstr_fd(str, 1);
	pthread_mutex_unlock(&philo->data->m_writing);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
