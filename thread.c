/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:15:02 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/18 15:36:32 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

int	ft_log(t_philo *philo, struct timeval time, char *str)
{
	char			*itoa;
	
	if (philo->data->live == 0)
	if (philo->data->live == 0)
		return (1);
	pthread_mutex_lock(&philo->data->writing);
	itoa = ft_itoa((time.tv_sec * 1000 + time.tv_usec / 1000) - philo->data->t_start);
	if (itoa == NULL)
		return (3);
	ft_putstr_fd(itoa, 1);
	ft_putstr_fd(" ", 1);
	free(itoa);
	itoa = ft_itoa(philo->id);
	if (itoa == NULL)
		return (3);
	ft_putstr_fd(itoa, 1);
	free(itoa);
	ft_putstr_fd(str, 1);
	itoa = ft_itoa((time.tv_sec * 1000 + time.tv_usec / 1000) - philo->data->t_start);
	if (itoa == NULL)
		return (3);
	ft_putstr_fd(itoa, 1);
	ft_putstr_fd(" ", 1);
	free(itoa);
	itoa = ft_itoa(philo->id);
	if (itoa == NULL)
		return (3);
	ft_putstr_fd(itoa, 1);
	free(itoa);
	ft_putstr_fd(str, 1);
	pthread_mutex_unlock(&philo->data->writing);
	return (0);
}

int	ft_lock(t_philo *philo)
int	ft_lock(t_philo *philo)
{
	struct timeval time;

	pthread_mutex_lock(&philo->l_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (ft_log(philo, time, " has taken a fork\n") == 3)
		return (3);
	if (philo->r_fork == NULL)
		return (pthread_mutex_unlock(&philo->l_fork), 1);
	pthread_mutex_lock(philo->r_fork);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (ft_log(philo, time, " has taken a fork\n") == 3)
		return (3);
	if (ft_log(philo, time, " has taken a fork\n") == 3)
		return (3);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	struct timeval time;

	if (ft_lock(philo) == 1)
		return (1);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (ft_log(philo, time, " is eating\n") == 3)
		return (3);
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	pthread_mutex_lock(&philo->t_l_eat);
	philo->t_last_eat = (time.tv_sec * 1000 + time.tv_usec / 1000);
	pthread_mutex_unlock(&philo->t_l_eat);
	if (usleep(philo->data->t_eat * 1000) == -1)
		return (3);
	pthread_mutex_lock(&philo->t_l_eat);
	philo->nb_eaten++;
	pthread_mutex_unlock(&philo->t_l_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	return (0);
}

int	ft_think(t_philo *philo)
{
	struct timeval	time;
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (ft_log(philo, time, " is thinking\n") == 3)
		return (3);
	if (usleep(philo->data->t_think * 1000) == -1)
	if (ft_log(philo, time, " is thinking\n") == 3)
		return (3);
	if (usleep(philo->data->t_think * 1000) == -1)
		return (3);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	struct timeval time;
	
	if (gettimeofday(&time, NULL) != 0)
		return (1);
	if (ft_log(philo, time, " is sleeping\n") == 3)
		return (3);
	if (usleep(philo->data->t_sleep * 1000) == -1)
	if (ft_log(philo, time, " is sleeping\n") == 3)
		return (3);
	if (usleep(philo->data->t_sleep * 1000) == -1)
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
		// if (philo->id == philo->data->nb_philo && philo->id % 2 != 0)
		// {
		// 	ret = ft_sleep(philo);
		// 	if (ret == 3)
		// 		return (NULL);
		// 	ret = ft_eat(philo);
		// 	if (ret != 0)
		// 		return (NULL);
		// 	ret = ft_think(philo);
		// 	if (ret == 3)
		// 		return (NULL);
		// }
		// else
		// {
			if (philo->id % 2 != 0)
			{
				ret = ft_eat(philo);
				if (ret != 0)
					return (NULL);
			}
			ret = ft_sleep(philo);
			if (ret == 3)
				return (NULL);
			ret = ft_think(philo);
			if (ret == 3)
				return (NULL);
			if (philo->id % 2 == 0)
			{
				ret = ft_eat(philo);
				if (ret != 0)
					return (NULL);
			}
		// }
	}
	return (NULL);
}
