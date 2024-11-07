/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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

int	ft_init_philos(t_data *data)
{
	int i;

	i = 1; 
	while (i <= data->nb_philo)
	{
		data->philo->id = i;
		data->philo->fork_id = i;
		pthread_mutex_init(data->philo->fork_id, NULL);
		data->philo->fork_status = 0;
		data->philo->nb_eaten = 0;
		data->philo->nb_philo = 0;
		data->philo->t_die = data->t_die;
		data->philo->t_eat = data->t_eat;
		data->philo->t_sleep = data->t_sleep;
		if (pthread_create(&data->philo[i].thread, NULL, ft_philos, &data->philo[i]) != 0)
			return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	pthread_t	*t_monitor;

	data = malloc(sizeof(t_data));
	if (!data)
		return (3);
	if (ft_check_args(argc, argv, data) == 1)
		return (1);
	if (pthread_create(&t_monitor, NULL, ft_monitor, data) != 0)
		return (1);
	if (ft_init_philos(data) == 1)
		return (1);
	return (0);
}