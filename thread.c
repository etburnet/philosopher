/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:15:02 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/19 14:37:46 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	ft_lock_odd(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->l_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	if (ft_log(philo, time, " has taken a fork\n") == 3)
		return (pthread_mutex_unlock(&philo->l_fork), 3);
	if (philo->r_fork == NULL)
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	pthread_mutex_lock(philo->r_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (ft_unlock(philo), 1);
	if (ft_log(philo, time, " has taken a fork\n") == 3)
		return (ft_unlock(philo), 3);
	return (0);
}

int	ft_lock_pair(t_philo *philo)
{
	struct timeval	time;

	if (philo->r_fork == NULL)
		return (1);
	pthread_mutex_lock(philo->r_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (pthread_mutex_unlock(philo->r_fork), 1);
	if (ft_log(philo, time, " has taken a fork\n") == 3)
		return (pthread_mutex_unlock(philo->r_fork), 3);
	pthread_mutex_lock(&philo->l_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (ft_unlock(philo), 1);
	if (ft_log(philo, time, " has taken a fork\n") == 3)
		return (ft_unlock(philo), 3);
	return (0);
}

int	ft_eat(t_philo *philo, int pair_odd)
{
	struct timeval	time;

	if (pair_odd == 1 && ft_lock_odd(philo) != 0)
		return (1);
	else if (pair_odd == 2 && ft_lock_pair(philo) != 0)
		return (1);
	if (gettimeofday(&time, NULL) != 0)
		return (ft_unlock(philo), 1);
	if (ft_log(philo, time, " is eating\n") == 3)
		return (ft_unlock(philo), 3);
	if (gettimeofday(&time, NULL) != 0)
		return (ft_unlock(philo), 1);
	pthread_mutex_lock(&philo->m_l_eat);
	philo->t_last_eat = (time.tv_sec * 1000 + time.tv_usec / 1000);
	pthread_mutex_unlock(&philo->m_l_eat);
	if (usleep(philo->data->t_eat * 1000) == -1)
		return (ft_unlock(philo), 3);
	pthread_mutex_lock(&philo->m_nb_eaten);
	philo->nb_eaten++;
	pthread_mutex_unlock(&philo->m_nb_eaten);
	ft_unlock(philo);
	return (0);
}

void	*ft_loop(t_philo *philo)
{
	if (philo->id % 2 != 0)
		if (ft_eat(philo, 1) != 0)
			return (NULL);
	if (ft_sleep(philo) != 0)
		return (NULL);
	if (ft_think(philo) != 0)
		return (NULL);
	if (philo->id % 2 == 0)
		if (ft_eat(philo, 2) != 0)
			return (NULL);
	return (NULL);
}

void	*ft_philos(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->data->m_live);
	while (philo->data->live)
	{
		pthread_mutex_unlock(&philo->data->m_live);
		if (philo->id == philo->data->nb_philo && philo->id % 2 != 0)
		{
			if (ft_sleep(philo) != 0)
				return (NULL);
			if (ft_eat(philo, 1) != 0)
				return (NULL);
			if (ft_think(philo) != 0)
				return (NULL);
		}
		else
			ft_loop(philo);
		pthread_mutex_lock(&philo->data->m_live);
	}
	pthread_mutex_unlock(&philo->data->m_live);
	return (NULL);
}
