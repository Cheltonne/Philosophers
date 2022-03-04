/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:41:46 by chajax            #+#    #+#             */
/*   Updated: 2022/03/04 18:49:01 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_shared
{
	char					**av;
	int						ac;
	int						total_ph;
	int						ttd;
	int						tte;
	int						tts;
	int						m_e;
	long int				start_time;
	struct s_philo			**ph;
	pthread_mutex_t			write_m;
}				t_shared;

typedef struct	s_philo
{
	pthread_t		t_id;
	int				id;
	pthread_mutex_t	l_f;
	pthread_mutex_t	*r_f;
	t_shared		*shared;
}				t_philo;

void		*routine(void* param);
void		sleep_think(t_philo *ph);
long int	ms_timeofday(void);
void		print_status(char *str, t_philo *philo);
void		init_shared(t_shared *data, int ac, char **av);
long long	ft_atoi(const char *str);
void		init_ph(t_shared *data);
t_philo		*add_philo(t_shared *data, int id);

#endif
