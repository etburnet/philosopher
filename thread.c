/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:15:02 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/07 16:36:11 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

int	ft_lock(t_philo *philo)
{
	if (philo[philo->id].fork_status == 0
		&& philo[philo->id +1].fork_status == 0)
	{
		pthread_mutex_lock(philo[philo->id].fork_id);
		pthread_mutex_lock(philo[philo->id + 1].fork_id);
		return (0);
	}
	else
		return (1);
}

void	ft_unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo[philo->id].fork_id);
	pthread_mutex_unlock(philo[philo->id + 1].fork_id);
}

int	ft_monitor(t_data *data)
{
	if (data->philo->id >= 0 && data->philo->id < data->philo->nb_philo)
	{
		if (ft_lock(data->philo[actuall]) == 0)
		{
			data->philo[actuall].fork_status = 1;
			data->philo[actuall].philo[data->philo->id + 1].fork_status = 1;
			return (0);
		}
		else
			return (1);
	}
	else if (data->philo[actuall].id == data->nb_philo)
	{
		if (ft_lock(data->philo[actuall]) == 0)
		{
			data->philo[data->philo->id].fork_status = 1;
			data->philo[0].fork_status = 1;
			return (0);
		}
		else
			return (1);
	}
	return (1);
}

int	ft_eat(t_philo *philo)
{
	int	ret;

	ret = pthread_join(philo->t_monitor, ret);
	if (ret == 0)
	{
		if (usleep(philo->data->t_eat) == -1)
			return (puts, 3);
		philo->nb_eaten++;
		ft_unlock(philo);
		return (0);
	}
	return (1);
}

void	ft_think(t_philo *philo)
{
	if (usleep(500) == -1)
		return (puts, 3);
}

void	ft_sleep(t_philo *philo)
{
	if (usleep(philo->data->t_sleep) == -1)
		return (puts, 3);
}

int	ft_philos(t_philo *philo)
{
	int	var_end;

	var_end = 1;
	while (var_end == 1)
	{
		if (ft_eat(philo) == 3)
			return (3);
		ft_sleep(philo);
		if (ft_eat(philo) == 3)
			return (3);
		ft_think(philo);
	}
	return (0);
}
