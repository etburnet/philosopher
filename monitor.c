/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:05:27 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/21 17:57:56 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_destroy(t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= philo->data->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].l_fork);
		pthread_mutex_destroy(&philo[i].m_l_eat);
		pthread_mutex_destroy(&philo[i].m_nb_eaten);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_is_dead(t_philo *philo, int i)
{
	long long		time;
	long int		die;

	time = ft_get_time();
	pthread_mutex_lock(&philo[i].m_l_eat);
	if (philo[i].data->t_die < (time - philo[i].t_last_eat))
	{
		pthread_mutex_unlock(&philo[i].m_l_eat);
		pthread_mutex_lock(&philo[i].data->m_live);
		philo->data->live = 0;
		pthread_mutex_unlock(&philo[i].data->m_live);
		die = time - philo->data->t_start;
		pthread_mutex_lock(&philo->data->m_writing);
		printf("%ld %d died\n", die, philo[i].id);
		pthread_mutex_unlock(&philo->data->m_writing);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo[i].m_l_eat);
	return (0);
}

void	ft_eaten(t_philo *philo, long int *i, long int *eat)
{
	pthread_mutex_lock(&philo[*i].m_nb_eaten);
	if (philo[*i].nb_eaten == philo->data->nb_eat)
		(*eat)++;
	pthread_mutex_unlock(&philo[*i].m_nb_eaten);
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
			if (ret != 0)
				return (ret);
			ft_eaten(philo, &i, &eat);
			i++;
		}
		if (philo->data->nb_philo == eat)
		{
			printf("All philos have eaten enough !\n");
			return (2);
		}
		usleep(4000);
	}
	return (0);
}
