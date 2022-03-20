/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:41:51 by chajax            #+#    #+#             */
/*   Updated: 2022/03/15 23:22:15 by chajax           ###   ########.fr       */
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

void	smart_sleep(long int time, t_philo *philo)
{
	long int	start_time;

	start_time = 0;
	start_time = ms_timeofday();
	while ((ms_timeofday() - start_time) < time)
	{
		if (ph_is_dead(philo) == TRUE)
			break ;
		usleep(50);
	}
}

void	print_status(char *str, t_philo *philo)
{
	long int	timestamp;

	timestamp = ms_timeofday() - philo->shared->start_time;
	if (ph_is_dead(philo) == FALSE)
		printf("%ld %d %s\n", timestamp, philo->id, str);
}
