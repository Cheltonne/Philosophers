/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:40:57 by chajax            #+#    #+#             */
/*   Updated: 2022/03/04 14:48:37 by chajax           ###   ########.fr       */
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
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	*routine(void *param)
{
	if ()
	printf("Philosopher is sleeping\n");
	return (param);
}

/*void	pthread_wait(t_shared *data)
{
	printf("Philosopher is thinking\n");
	pthread_join()
}*/

int	main(int ac, char **av)
{
	t_shared			data;

	init_shared(&data, ac, av);
	init_ph(&data);
}
