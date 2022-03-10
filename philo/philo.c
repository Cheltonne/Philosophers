/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:40:57 by chajax            #+#    #+#             */
/*   Updated: 2022/03/09 22:38:38 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_fct(void *param)
{
	t_philo	*philo;

	philo = param;
	while (!philo->shared->ph_dead)
	{
		pthread_create(&philo->shared->death_id, NULL, &check_death, philo);
		routine(philo);
		pthread_detach(philo->shared->death_id);
	}
	return (param);
}

void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->shared->tte * 1000);
	pthread_mutex_lock(&philo->l_f);
	pthread_mutex_lock(&philo->shared->write_m);
	print_status("has taken a fork", philo);
	pthread_mutex_unlock(&philo->shared->write_m);

	pthread_mutex_lock(philo->r_f);
	pthread_mutex_lock(&philo->shared->write_m);
	print_status("has taken a fork", philo);
	pthread_mutex_unlock(&philo->shared->write_m);

	pthread_mutex_lock(&philo->shared->write_m);
	print_status("is eating", philo);
	philo->last_eat = ms_timeofday();
	pthread_mutex_unlock(&philo->shared->write_m);
	usleep(philo->shared->tte * 1000);
	pthread_mutex_unlock(philo->r_f);
	pthread_mutex_unlock(&philo->l_f);

	pthread_mutex_lock(&philo->shared->write_m);
	print_status("is sleeping", philo);
	pthread_mutex_unlock(&philo->shared->write_m);
	usleep(philo->shared->tts * 1000);

	pthread_mutex_lock(&philo->shared->write_m);
	print_status("is thinking", philo);
	pthread_mutex_unlock(&philo->shared->write_m);
	return ;
}

void	*check_death(void *param)
{
	t_philo *philo;

	philo = param;
	usleep(philo->shared->ttd);
	if ((ms_timeofday() - philo->last_eat) >= philo->shared->ttd)
	{
		pthread_mutex_lock(&philo->shared->death_m);
		pthread_mutex_lock(&philo->shared->write_m);
		print_status("died", philo);
		pthread_mutex_unlock(&philo->shared->write_m);
		philo->shared->ph_dead = 1;
		pthread_mutex_unlock(&philo->shared->death_m);
		return (NULL);
	}
	return (NULL);	
}

int	main(int ac, char **av)
{
	t_shared	*data;

	data = ft_calloc(1, sizeof(t_shared));
	if (data == NULL)
		return (0);
	init_shared(data, ac, av);
	init_ph(data);
	threads(data);
	free_fct(data);
	free(data);
}
