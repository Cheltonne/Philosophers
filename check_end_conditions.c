/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_conditions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:14:56 by chajax            #+#    #+#             */
/*   Updated: 2022/03/20 17:15:16 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->death_m);
	if (philo->shared->ph_dead == TRUE)
	{
		pthread_mutex_unlock(&philo->shared->death_m);
		return (TRUE);
	}
	else
	{
		pthread_mutex_unlock(&philo->shared->death_m);
		return (FALSE);
	}
}

void	*check_death(void *param)
{
	t_philo	*philo;

	philo = param;
	smart_sleep(philo->shared->ttd, philo);
	pthread_mutex_lock(&philo->eat_m);
	if ((ms_timeofday() - philo->last_eat) >= philo->shared->ttd)
	{
		pthread_mutex_unlock(&philo->eat_m);
		pthread_mutex_lock(&philo->shared->write_m);
		print_status("died", philo);
		pthread_mutex_unlock(&philo->shared->write_m);
		pthread_mutex_lock(&philo->shared->death_m);
		philo->shared->ph_dead = TRUE;
		pthread_mutex_unlock(&philo->shared->death_m);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->eat_m);
	return (NULL);
}

void	all_meals_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->done_m);
	if (philo->shared->done_eating == philo->shared->total_ph)
	{
		pthread_mutex_lock(&philo->shared->write_m);
		print_status(NULL, philo);
		pthread_mutex_unlock(&philo->shared->write_m);
		pthread_mutex_unlock(&philo->shared->done_m);
		pthread_mutex_lock(&philo->shared->death_m);
		philo->shared->ph_dead = TRUE;
		pthread_mutex_unlock(&philo->shared->death_m);
	}
	pthread_mutex_unlock(&philo->shared->done_m);
}
