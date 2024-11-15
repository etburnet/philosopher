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
	long int	nb_philo;
	long int	t_die;
	long int	t_eat;
	long int	t_think;
	long int	t_start;
	long int	t_sleep;
	int			live;
	long int	nb_eat;
	char		*msg;
	long int	msg_id;
} t_data;

typedef struct	s_philo
{
	t_data		*data;
	pthread_t 	thread;
	long int	id;
	long int	nb_eaten;
	int			fork_status;
	long int 	nb_philo;
	long int	t_last_eat;
	pthread_mutex_t l_fork;
	pthread_mutex_t *r_fork;
} t_philo;

int		ft_atoi(char *str);
int		ft_strlen(char *str);
int		ft_isdigit(char n);
void	ft_putstr_fd(char *s, int fd);
void	*ft_philos(void *p);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);
int		ft_monitor(t_philo *philo);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

#endif