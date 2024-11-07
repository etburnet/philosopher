/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 09:11:16 by eburnet           #+#    #+#             */
/*   Updated: 2024/08/28 09:11:16 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOS_H
# define FT_PHILOS_H
# include <stdio.h>
# include <unistd.h> 
# include <pthread.h>

typedef struct	s_philo
{
	pthread_t 	*thread;
	int			 id;
	long int	nb_eaten;
	int			fork_status;
	int			nb_philo;
	int			fork_id;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			nb_eat;
} t_philo;

typedef struct	s_data
{
	int	nb_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_eat;
	t_philo philo[200];
} t_data;

int		ft_atoi(char *str);
int		ft_isdigit(char n);
void	ft_putstr_fd(char *s, int fd);
int		ft_philos(t_data *data, int	id);
int		ft_monitor(t_data *data, int id);

#endif