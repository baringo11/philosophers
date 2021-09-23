/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:58:30 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/23 15:45:12 by jbaringo         ###   ########.fr       */
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
	suseconds_t	time_before_eat;
	int			is_alive;
	int			state[3];

}				t_philo;

typedef struct	s_all
{
	int				num_philos;
	pthread_mutex_t	index_mutex;
	int				index;
	int				is_alive;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				flag_iterations;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	
	uint64_t		start_time;
	uint64_t		current_time;

	t_philo			*philo;

}				t_all;

int		threads(t_all *all);
int		str_error(char	*error);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);