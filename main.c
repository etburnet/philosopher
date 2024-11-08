/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/08/28 09:08:13 by eburnet           #+#    #+#             */
/*   Updated: 2024/08/28 09:08:13 by eburnet          ###   ########.fr       */
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
		philo->data->nb_eat = 0;
	return (0);
}

int	ft_init_philos(t_philo *philo)
{
	int i;
	pthread_mutex_t	*p_fork;
	struct timeval start;

	i = 1;
	if (gettimeofday(&start, NULL) != 0)
		return (1);
	philo->data->t_start = start.tv_usec;
	while (i <= philo->data->nb_philo)
	{
		philo[i].id = i;
		if (i != 1)
			philo[i].r_fork = p_fork;
		pthread_mutex_init(&philo[i].l_fork, NULL);
		philo[i].fork_status = 0;
		philo[i].nb_eaten = 0;
		p_fork = &philo[i].l_fork;
		i++;
	}
	philo[1].r_fork = p_fork;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo philo[200];
	int i;

	i = 1;
	philo->data = malloc(sizeof(t_data));
	if (philo->data == NULL)
		return (3);
	if (ft_check_args(argc, argv, philo) != 0)
		return (1);
	if (ft_init_philos(philo) != 0)
		return (1);
/* 	if (pthread_create(&philo->data->t_monitor, NULL, ft_monitor, philo->data) != 0)
		return (1); */
	while (i <= philo->data->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, ft_philos, &philo[i]) != 0)
			return (1);
		i++;
	}
	i = 1;
	while (i <= philo->data->nb_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
		pthread_mutex_destroy(&philo[i].l_fork);
		i++;
	}
/* 	if (pthread_join(&philo->data->t_monitor, NULL) != 0)
		return (1); */
	return (0);
}
