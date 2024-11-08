/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:15:02 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/08 16:50:48 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

void	ft_lock(t_philo *philo)
{
	ft_putstr_fd("Lock\n", 1);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
}

void	ft_unlock(t_philo *philo)
{
	ft_putstr_fd("Unlock\n", 1);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
}

/* int	ft_monitor(t_philo philo)
{

} */

int	ft_eat(t_philo *philo)
{
	ft_putstr_fd("Eating\n", 1);
	ft_lock(philo);
	if (usleep(philo->data->t_eat) == -1)
		return (3);
	philo->nb_eaten++;
	ft_unlock(philo);
	return (0);
}

int	ft_think()
{
	ft_putstr_fd("Thinking\n", 1);
	if (usleep(500) == -1)
		return (3);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_putstr_fd("Sleeping\n", 1);
	if (usleep(philo->data->t_sleep) == -1)
		return (3);
	return (0);
}

void	*ft_philos(void *p)
{
	t_philo *philo;
	int		*ret;

	ret = 0;
	philo = (t_philo *)&p;
	while (1)
	{
		ft_putstr_fd("ft_philo id: ", 1);
		ft_putstr_fd(ft_itoa(philo->id), 1);
		ft_putstr_fd("\n", 1);
		if (philo->id % 2 == 0)
		{
			*ret = ft_eat(philo);
			if (*ret == 3)
				return (ret);
		}
		*ret = ft_sleep(philo);
		if (*ret == 3)
			return (ret);
		if (philo->id % 2 != 0)
		{
			*ret = ft_eat(philo);
			if (*ret == 3)
				return (ret);
		}
		*ret = ft_think();
		if (*ret == 3)
			return (ret);
	}
	return (ret);
}
