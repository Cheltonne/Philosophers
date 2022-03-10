/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 19:27:31 by chajax            #+#    #+#             */
/*   Updated: 2022/03/09 22:33:35 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->pa->write_m);
	state_change("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->pa->write_m);
	ft_usleep(ph->shared->tts);
	pthread_mutex_lock(&ph->pa->write_m);
	state_change("is thinking\n", ph);
	pthread_mutex_unlock(&ph->pa->write_m);
}
