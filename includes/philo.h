/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:58:30 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/28 20:18:31 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_philo
{
	int			num_iterations;
	suseconds_t	last_time_eat;
	int			is_alive;
}				t_philo;

typedef struct	s_all
{
	int				num_philos;
	pthread_mutex_t	index_mutex;
	int				index;
	int				is_alive;
	pthread_mutex_t	print;
	__uint64_t		start_time;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				flag_iterations;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}				t_all;

__uint64_t		time_in_ms();
void			print_status(char *status, int index, t_all *all);
void			*main_routine(t_all *all);
int				threads(t_all *all);
int				str_error(char	*error);
int				ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);