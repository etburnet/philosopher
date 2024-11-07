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


int	ft_check_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (printf("4 or 5 args no more, no less\n"), 1);
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo <= 0 || data->nb_philo > 200)
		return (printf("nb_philo, invalid arg\n"), 1);
	data->t_die = ft_atoi(argv[2]);
	if (data->t_die <= 0)
		return (printf("t_die, invalid arg\n"), 1);
	data->t_eat = ft_atoi(argv[3]);
	if (data->t_eat <= 0)
		return (printf("t_eat, invalid arg\n"), 1);
	data->t_sleep = ft_atoi(argv[4]);
	if (data->t_sleep <= 0)
		return (printf("t_sleep, invalid arg\n"), 1);
	if (argc == 6)
	{
		data->nb_eat = ft_atoi(argv[5]);
		if (data->nb_eat < 0)
			return (printf("nb_eat, invalid arg\n"), 1);
	}
	return (0);
}

int	ft_init_philos(t_philo *philo)
{
	int i;
	int ret;

	i = 1;
	while (i <= philo->data->nb_philo)
	{
		philo[i].id = i;
		philo[i].fork_id = i;
		pthread_mutex_init(philo[i].fork_id, NULL);
		philo[i].fork_status = 0;
		philo[i].nb_eaten = 0;
		ret = pthread_create(&philo[i].thread, NULL, ft_philos,
				&philo[i]);
		if (ret != 0)
			return (ret);
		ret = pthread_detach(&philo[i].thread);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo philo[200];

	philo->data = NULL;
	if (ft_check_args(argc, argv, philo->data) != 0)
		return (1);
	if (pthread_create(&philo->data->t_monitor, NULL, ft_monitor, philo->data) != 0)
		return (1);
	if (ft_init_philos(philo) != 0)
		return (1);
	return (0);
}