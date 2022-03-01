/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:41:46 by chajax            #+#    #+#             */
/*   Updated: 2022/03/01 17:34:23 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_philo
{
	pthread_t		t_id;
	int				id;
	pthread_mutex_t	l_f;
	pthread_mutex_t	*r_f;
}				t_philo;

typedef struct	s_data
{
	char	**av;
	int		ac;
	int		total_ph;
	int		ttd;
	int		tte;
	int		tts;
	int		m_e;
	t_philo	**ph;
}				t_data;

void		*routine(void* param);
long int	actual_time(void);
void		init_data(t_data *data, int ac, char **av);
long long	ft_atoi(const char *str);
void		init_ph(t_data *data);
t_philo		*add_philo(t_data *data, int id);

#endif
