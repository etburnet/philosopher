/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:00:10 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/19 14:00:10 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	pthread_t		t_monitor;
	pthread_mutex_t	m_writing;
	pthread_mutex_t	m_live;
	long int		nb_philo;
	long int		t_die;
	long int		t_eat;
	long int		t_think;
	long int		t_start;
	long int		t_sleep;
	int				live;
	long int		nb_eat;
	long int		msg_id;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread;
	int				id;
	long int		nb_eaten;
	int				fork_status;
	long int		nb_philo;
	long int		t_last_eat;
	pthread_mutex_t	m_nb_eaten;
	pthread_mutex_t	m_l_eat;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;

int			ft_atoi(char *str);
int			ft_strlen(char *str);
int			ft_isdigit(char n);
void		ft_putstr_fd(char *s, int fd);
void		*ft_philos(void *p);
char		*ft_strdup(const char *s);
char		*ft_itoa(int n);
int			ft_monitor(t_philo *philo);
int			ft_log(t_philo *philo, long long time, char *str);
int			ft_sleep(t_philo *philo);
int			ft_think(t_philo *philo);
void		ft_unlock(t_philo *philo);
void		ft_destroy(t_philo *philo);
int			ft_is_live(t_philo *philo);
long long	ft_get_time(void);
void		ft_usleep(long long time, t_philo *philo);

#endif