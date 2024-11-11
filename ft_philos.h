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
# include <sys/time.h>
# include <stdlib.h>

typedef struct	s_data
{
	pthread_t	t_monitor;
	pthread_mutex_t writing;
	int	nb_philo;
	int	t_die;
	int	t_start;
	int	t_eat;
	int	t_sleep;
	int	nb_eat;
} t_data;

typedef struct	s_philo
{
	t_data		*data;
	pthread_t 	thread;
	int			 id;
	long int	nb_eaten;
	int			fork_status;
	int			nb_philo;
	pthread_mutex_t l_fork;
	pthread_mutex_t *r_fork;
} t_philo;

int		ft_atoi(char *str);
int		ft_isdigit(char n);
void	ft_putstr_fd(char *s, int fd);
void	*ft_philos(void *p);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);
// int		ft_monitor(t_philo philo);

#endif