/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:05:27 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/15 12:18:24 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

int	ft_is_dead(t_philo *philo, int i)
{
	struct timeval time;
	long int die;
	
	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	if (philo[i].data->t_die < ((time.tv_sec * 1000 + time.tv_usec / 1000) - philo[i].t_last_eat))
	{
		philo->data->live = 0;
		die = (time.tv_sec * 1000 + time.tv_usec / 1000) - philo->data->t_start;
		pthread_mutex_lock(&philo->data->writing);
		printf("%ld %ld died\n", die, philo[i].id);
		pthread_mutex_unlock(&philo->data->writing);
		return (1);
	}
	return (0);
}

int	ft_monitor(t_philo *philo)
{
	long int	i;
	long int	eat;
	int			ret;

	while (1)
	{
		eat = 0;
		i = 1;
		while (i <= philo->data->nb_philo)
		{
			ret = ft_is_dead(philo, i);
			if (ret == 1)
				return (1);
			else if (ret == -1)
				return (-1);
			if (philo[i].nb_eaten == philo->data->nb_eat)
				eat++;
			i++;
		}
		if (philo->data->nb_philo == eat)
		{
			philo->data->msg = ft_strdup("All philos have eaten enough !");
			return (2);
		}
		//usleep(400);
	}
	return (0);
}
