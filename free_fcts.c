/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <chajax@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:52:37 by chajax            #+#    #+#             */
/*   Updated: 2022/03/14 17:10:46 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_shared *shared)
{
	pthread_mutex_destroy(&shared->write_m);
	pthread_mutex_destroy(&shared->death_m);
	pthread_mutex_destroy(&shared->done_m);
}

void	free_fct(t_shared *data)
{
	int i;

	i = 0;
	while (i < data->total_ph + 1)
	{
		free(data->ph[i]);
		i++;
	}
	free(data->ph);
	destroy_mutexes(data);
}
