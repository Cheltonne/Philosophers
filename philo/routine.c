/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:27:31 by chajax            #+#    #+#             */
/*   Updated: 2022/03/11 18:11:54 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->shared->ph_dead == 0)
	{
		pthread_mutex_lock(&philo->shared->write_m);
		philo->last_eat = ms_timeofday();
		print_status("is eating", philo);
		pthread_mutex_unlock(&philo->shared->write_m);
		usleep(philo->shared->tte * 1000);
		philo->nb_eat++;
		if (philo->nb_eat == philo->shared->total_meals)
		{
			pthread_mutex_lock(&philo->shared->done_m);
			philo->shared->all_done++;
			pthread_mutex_unlock(&philo->shared->done_m);
		}
		pthread_mutex_unlock(philo->r_f);
		pthread_mutex_unlock(&philo->l_f);
	}
}

void	sleep_think(t_philo *philo)
{
	if (philo->shared->ph_dead == 0)
	{
		pthread_mutex_lock(&philo->shared->write_m);
		print_status("is sleeping", philo);
		pthread_mutex_unlock(&philo->shared->write_m);
		usleep(philo->shared->tts * 1000);
		pthread_mutex_lock(&philo->shared->write_m);
		print_status("is thinking", philo);
		pthread_mutex_unlock(&philo->shared->write_m);
	}
}
