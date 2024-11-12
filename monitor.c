/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:05:27 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/12 15:08:33 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

int	ft_is_dead(t_philo *philo, int i)
{
	struct timeval time;
	
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (philo[i].data->t_die < (time.tv_usec - philo[i].t_last_eat))
	{
		philo->data->msg_t =  time.tv_usec - philo->data->t_start;
		philo->data->msg_id = philo[i].id;
		return (1);
	}
	return (0);
}

int	ft_monitor(t_philo *philo)
{
	int	i;
	int	eat;

	eat = 0;
	while (1)
	{
		i = 0;
		while (i <= philo->data->nb_philo)
		{
			if (ft_is_dead(philo, i) != 0)
				return (-1);
			if (philo[i].nb_eaten == philo->data->nb_eat)
				eat++;
			i++;
		}
		if (philo->data->nb_philo == eat)
		{
			philo->data->msg = ft_strdup("All philos have eaten enough !");
			return (1);
		}
	}
	return (0);
}
