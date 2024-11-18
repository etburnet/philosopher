/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:02:25 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/12 13:02:25 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

int	ft_check_args(int argc, char **argv, t_philo *philo)
{
	if (argc < 5 || argc > 6)
		return (printf("4 or 5 args no more, no less\n"), 1);
	philo->data->nb_philo = ft_atoi(argv[1]);
	if (philo->data->nb_philo <= 0 || philo->data->nb_philo > 200)
		return (printf("nb_philo, invalid arg\n"), 1);
	philo->data->t_die = ft_atoi(argv[2]);
	if (philo->data->t_die <= 0)
		return (printf("t_die, invalid arg\n"), 1);
	philo->data->t_eat = ft_atoi(argv[3]);
	if (philo->data->t_eat <= 0)
		return (printf("t_eat, invalid arg\n"), 1);
	philo->data->t_sleep = ft_atoi(argv[4]);
	if (philo->data->t_sleep <= 0)
		return (printf("t_sleep, invalid arg\n"), 1);
	if (argc == 6)
	{
		philo->data->nb_eat = ft_atoi(argv[5]);
		if (philo->data->nb_eat < 0)
			return (printf("nb_eat, invalid arg\n"), 1);
	}
	else
		philo->data->nb_eat = -1;
	pthread_mutex_init(&philo->data->writing, NULL);
	philo->data->t_think = (philo->data->t_die - (philo->data->t_eat + philo->data->t_sleep)) / 2;
	if (philo->data->t_think < 0)
		philo->data->t_think = 1;
	philo->data->live = 1;
	return (0);
}

int	ft_init_philos(t_philo *philo)
{
	int i;
	struct timeval start;

	i = 1;
	if (gettimeofday(&start, NULL) != 0)
		return (1);
	philo->data->t_start = (start.tv_sec * 1000 + start.tv_usec / 1000);
	while (i <= philo->data->nb_philo)
	{
		philo[i].data = philo->data;
		philo[i].id = i;
		if (i > 1)
			philo[i].r_fork = &philo[i - 1].l_fork;
		pthread_mutex_init(&philo[i].l_fork, NULL);
		pthread_mutex_init(&philo[i].t_l_eat, NULL);
		philo[i].fork_status = 0;
		philo[i].nb_eaten = 0;
		philo[i].t_last_eat = (start.tv_sec * 1000 + start.tv_usec / 1000);
		i++;
	}
	philo[1].r_fork = &philo[philo->data->nb_philo].l_fork;
	if (philo->data->nb_philo == 1)
		philo[1].r_fork = NULL;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo philo[200];
	int i;
	int ret;
	struct timeval time;

	if (gettimeofday(&time, NULL) != 0)
		return (1);
	i = 1;
	philo->data = malloc(sizeof(t_data));
	if (philo->data == NULL)
		return (3);
	if (ft_check_args(argc, argv, philo) != 0)
		return (free(philo->data), 1);
	if (ft_init_philos(philo) != 0)
		return (free(philo->data), 1);
	while (i <= philo->data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_philos, &philo[i]) != 0)
			return (free(philo->data), 1);
		i++;
	}
	ret = ft_monitor(philo);
	philo->data->live = 0;
	i = 1;
	while (i <= philo->data->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (free(philo->data), 1);
		pthread_mutex_destroy(&philo[i].l_fork);
		pthread_mutex_destroy(&philo[i].t_l_eat);
		i++;
	}
	if (ret == 2)
	{
		pthread_mutex_lock(&philo->data->writing);
		printf("%s\n", philo->data->msg);
		pthread_mutex_unlock(&philo->data->writing);
		free(philo->data->msg);
	}
	return (free(philo->data), ret);
}
