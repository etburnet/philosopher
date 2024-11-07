/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:15:02 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/07 13:46:55 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

int	ft_lock(t_data *data, int  left_f, int right_f)
{
	if (data->philo[left_f].fork_status == 0 && data->philo[right_f].fork_status == 0)
		pthread_mutex_lock();
}

int	ft_monitor(t_data *data, int id)
{
	if (id >= 0 && id < data->nb_philo)
	{
		if (ft_lock(data, id, id + 1) == 0)
		{
			data->philo[id].fork_status = 1;
			data->philo[id + 1].fork_status = 1;
			return (0);
		}
		else
			return (1);
	}
	else if (id == data->nb_philo)
	{
		if (ft_lock(data, id, 0) == 0)
		{
			data->philo[id].fork_status = 1;
			data->philo[0].fork_status = 1;
			return (0);
		}
		else
			return (1);
	}
	return (1);
}

int	ft_eat(t_philo *philo, int id)
{
	if (ft_monitor == 0)
	{
		if (usleep(philo->t_eat) == -1)
			return (puts, 3);
		philo->nb_eaten++;
		ft_unlock(philo, id);
		return (0);
	}
	return (1);
}

int	ft_philos(t_philo *philo, int	id)
{
	int	var_end;

	var_end = 1;
	while (var_end == 1)
	{
		if (ft_eat(philo, id) == 3)
			return (3);
		ft_sleep(philo, id);
		if (ft_eat(philo, id) == 3)
			return (3);
		ft_think(philo, id);
	}
}
