/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:41:46 by chajax            #+#    #+#             */
/*   Updated: 2022/03/11 18:10:51 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define TRUE 1
# define FALSE 0
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
	int						total_meals;
	int						all_done;
	int						ph_dead;
	long int				start_time;
	struct s_philo			**ph;
	pthread_mutex_t			write_m;
	pthread_mutex_t			death_m;
	pthread_mutex_t			done_m;
}				t_shared;

typedef struct	s_philo
{
	pthread_t		t_id;
	pthread_t		death_id;
	int				id;
	int				nb_eat;
	long int		last_eat;
	pthread_mutex_t	l_f;
	pthread_mutex_t	*r_f;
	t_shared		*shared;
}				t_philo;

void		*thread_fct(void *param);
void		routine(t_philo *philo);
void		*check_death(void *param);
void		eat(t_philo *philo);
void		sleep_think(t_philo *philo);
long int	ms_timeofday(void);
void		print_status(char *str, t_philo *philo);
void		init_shared(t_shared *data, int ac, char **av);
long long	ft_atoi(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
void		init_ph(t_shared *data);
void		add_philo(t_shared *data, t_philo *ret, int id);
void		threads(t_shared *data);
void		free_fct(t_shared * data);

#endif
