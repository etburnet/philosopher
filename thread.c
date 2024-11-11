/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:15:02 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/11 14:06:13 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

void	ft_lock(t_philo *philo)
{
	if (philo->r_fork == NULL || &(philo->l_fork) == NULL)
		return ft_putstr_fd("err", 2);
	// pthread_mutex_lock(&philo->data->writing);
	// ft_putstr_fd("Philo ", 1);
	// ft_putstr_fd(ft_itoa(philo->id), 1);
	// ft_putstr_fd(" Lock\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
}

void	ft_unlock(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->writing);
	// ft_putstr_fd("Philo ", 1);
	// ft_putstr_fd(ft_itoa(philo->id), 1);
	// ft_putstr_fd(" Unlock\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
}

/* int	ft_monitor(t_philo philo)
{

} */

int	ft_eat(t_philo *philo)
{
	(void)philo;
	pthread_mutex_lock(&philo->data->writing);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" is eating\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	ft_lock(philo);
	if (usleep(philo->data->t_eat) == -1)
		return (3);
	philo->nb_eaten++;
	ft_unlock(philo);
	return (0);
}

int	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->writing);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" is thinking\n", 1);
	pthread_mutex_unlock(&philo->data->writing);
	if (usleep(500) == -1)
		return (3);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->writing);
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
	while (1)
	{
		// pthread_mutex_lock(&philo->data->writing);
		// ft_putstr_fd("ft_philo id: ", 1);
		// ft_putstr_fd(ft_itoa(philo->id), 1);
		// ft_putstr_fd("\n", 1);
		// pthread_mutex_unlock(&philo->data->writing);
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
