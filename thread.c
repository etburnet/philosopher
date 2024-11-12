/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:15:02 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/12 15:22:32 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

int	ft_lock(t_philo *philo)
{
	struct timeval time;
	
	if (philo->r_fork == NULL || &(philo->l_fork) == NULL)
		return (1);
	pthread_mutex_lock(philo->r_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->writing);
	ft_putstr_fd(ft_itoa(time.tv_usec- philo->data->t_start), 1);
	ft_putstr_fd(" ms ", 1);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" has taken right fork\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	pthread_mutex_lock(&philo->l_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->writing);
	ft_putstr_fd(ft_itoa(time.tv_usec - philo->data->t_start), 1);
	ft_putstr_fd(" ms ", 1);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" has taken left fork\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	return (0);
}

int	ft_unlock(t_philo *philo)
{
	struct timeval time;
	
	pthread_mutex_unlock(philo->r_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->writing);
	ft_putstr_fd(ft_itoa(time.tv_usec - philo->data->t_start), 1);
	ft_putstr_fd(" ms ", 1);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" has dropped right fork\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	pthread_mutex_unlock(&philo->l_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->writing);
	ft_putstr_fd(ft_itoa(time.tv_usec - philo->data->t_start), 1);
	ft_putstr_fd(" ms ", 1);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" has dropped left fork\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (ft_lock(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->data->writing);
	ft_putstr_fd(ft_itoa(time.tv_usec - philo->data->t_start), 1);
	ft_putstr_fd(" ms ", 1);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" is eating\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	philo->t_last_eat = time.tv_usec;
	if (usleep(philo->data->t_eat) == -1)
		return (3);
	philo->nb_eaten++;
	if (ft_unlock(philo) == 1)
		return (1);
	return (0);
}

int	ft_think(t_philo *philo)
{
	struct timeval time;
	
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->writing);
	ft_putstr_fd(ft_itoa(time.tv_usec - philo->data->t_start), 1);
	ft_putstr_fd(" ms ", 1);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" is thinking\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	if (usleep(philo->data->t_think) == -1)
		return (3);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	struct timeval time;
	
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	pthread_mutex_lock(&philo->data->writing);
	ft_putstr_fd(ft_itoa(time.tv_usec - philo->data->t_start), 1);
	ft_putstr_fd(" ms ", 1);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" is sleeping\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	if (usleep(philo->data->t_sleep) == -1)
		return (3);
	return (0);
}

void	*ft_philos(void *p)
{
	t_philo *philo;
	int		ret;

	philo = (t_philo *)p;
	while (philo->data->live)
	{
		if (philo->id % 2 == 0)
		{
			ret = ft_eat(philo);
			if (ret == 3)
				return (NULL);
		}
		ret = ft_sleep(philo);
		if (ret == 3)
			return (NULL);
		if (philo->id % 2 != 0)
		{
			ret = ft_eat(philo);
			if (ret == 3)
				return (NULL);
		}
		ret = ft_think(philo);
		if (ret == 3)
			return (NULL);
	}
	return (NULL);
}
