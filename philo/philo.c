/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:40:57 by chajax            #+#    #+#             */
/*   Updated: 2022/03/04 18:51:04 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->id % 2 == 0)
		usleep(0.5);
	pthread_mutex_lock(&philo->shared->write_m);
	pthread_mutex_lock(&philo->l_f);
	print_status("has taken a fork", philo);
	pthread_mutex_unlock(&philo->shared->write_m);
	pthread_mutex_lock(&philo->shared->write_m);
	pthread_mutex_lock(philo->r_f);
	print_status("has taken a fork", philo);
	pthread_mutex_unlock(&philo->shared->write_m);
	pthread_mutex_unlock(philo->r_f);
	pthread_mutex_unlock(&philo->l_f);
	pthread_mutex_lock(&philo->shared->write_m);
	print_status("is thinking", philo);
	pthread_mutex_unlock(&philo->shared->write_m);
	return (param);
}

int	main(int ac, char **av)
{
	t_shared	*data;

	data = malloc(sizeof(t_shared));
	if (data == NULL)
		return (0);
	init_shared(data, ac, av);
	init_ph(data);
	free(data);
}
