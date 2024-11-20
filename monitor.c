/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:05:27 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/20 12:05:54 by eburnet          ###   ########.fr       */
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
	struct timeval	time;
	long int		die;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	pthread_mutex_lock(&philo[i].m_l_eat);
	if (philo[i].data->t_die < ((time.tv_sec * 1000 + time.tv_usec / 1000)
			- philo[i].t_last_eat))
	{
		pthread_mutex_unlock(&philo[i].m_l_eat);
		pthread_mutex_lock(&philo[i].data->m_live);
		philo->data->live = 0;
		pthread_mutex_unlock(&philo[i].data->m_live);
		die = (time.tv_sec * 1000 + time.tv_usec / 1000) - philo->data->t_start;
		pthread_mutex_lock(&philo->data->m_writing);
		printf("%ld %ld died\n", die, philo[i].id);
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
			philo->data->msg = ft_strdup("All philos have eaten enough !");
			return (2);
		}
		usleep(8000);
	}
	return (0);
}
