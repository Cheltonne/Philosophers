/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:41:51 by chajax            #+#    #+#             */
/*   Updated: 2022/03/11 18:35:45 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ms_timeofday(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
		return(0);
	time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return (time);
}

void	print_status(char *str, t_philo *philo)
{
	long int	timestamp;

	timestamp = ms_timeofday() - philo->shared->start_time;
	if (philo->shared->ph_dead == 0 && philo->shared->all_done != philo->shared->total_ph)
		printf("%ld %d %s\n", timestamp, philo->id, str);
}
