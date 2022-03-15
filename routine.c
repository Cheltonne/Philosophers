/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:27:31 by chajax            #+#    #+#             */
/*   Updated: 2022/03/15 23:14:21 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_ph_fct(void *param)
{
	t_philo *philo;

	philo = param;

	pthread_mutex_lock(&philo->l_f);
	pthread_mutex_lock(&philo->shared->write_m);
	print_status("has taken a fork", philo);
	pthread_mutex_unlock(&philo->shared->write_m);
	smart_sleep(philo->shared->ttd, philo);
	pthread_mutex_lock(&philo->shared->write_m);
	print_status("died", philo);
	pthread_mutex_unlock(&philo->shared->write_m);
	pthread_mutex_unlock(&philo->l_f);
	return (NULL);
}

void	eat(t_philo *philo)
{
		pthread_mutex_lock(&philo->eat_m);
		philo->last_eat = ms_timeofday();
		pthread_mutex_unlock(&philo->eat_m);
		print_status("is eating", philo);
		smart_sleep(philo->shared->tte, philo);
		philo->nb_eat++;
		if (philo->nb_eat == philo->shared->total_meals)
		{
			pthread_mutex_lock(&philo->shared->done_m);
			philo->shared->done_eating++;
			pthread_mutex_unlock(&philo->shared->done_m);
		}
}

void	sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->death_m);
	if (philo->shared->ph_dead == 0)
	{
		pthread_mutex_unlock(&philo->shared->death_m);
		print_status("is sleeping", philo);
		smart_sleep(philo->shared->tts, philo);
		print_status("is thinking", philo);
	}
}
