/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:40:46 by chajax            #+#    #+#             */
/*   Updated: 2022/03/09 23:03:57 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_philo(t_shared *data, t_philo *ret, int id)
{
	ret->id = id;
	ret->last_eat = data->start_time;
	pthread_mutex_init(&ret->l_f, NULL);
	if (id == data->total_ph)
		ret->r_f = &data->ph[0]->l_f;
	else
		ret->r_f = &data->ph[id]->l_f;
	ret->shared = data;
}

void	init_ph(t_shared *data)
{
	int	i;

	i = 0;
	while (i < data->total_ph+1)
	{
		data->ph[i] = ft_calloc(1, sizeof(t_philo));
		i++;
	}
	i = 0;
	while(i < data->total_ph)
	{
		add_philo(data, data->ph[i], i + 1);
		i++;
	}
	i = 0;
}

void	init_shared(t_shared *data, int ac, char **av)
{
	data->ph = ft_calloc(ft_atoi(av[1]) + 1, sizeof(t_philo *));
	if (data->ph == NULL)
		return ;
	data->av = av;
	data->ac = ac;
	data->total_ph = ft_atoi(av[1]);
	data->ttd = ft_atoi(av[2]);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	if (av[5])
		data->m_e = ft_atoi(av[5]);
	data->start_time = ms_timeofday();
	data->ph_dead = 0;
	pthread_mutex_init(&data->write_m, NULL);
	pthread_mutex_init(&data->death_m, NULL);
}

void	threads(t_shared *data)
{
	int i;

	i = 0;
	while(i < data->total_ph)
	{
		pthread_create(&data->ph[i]->t_id, NULL, &thread_fct, data->ph[i]);
		i++;
	}
	i = 0;
	while(i < data->total_ph)
	{
		pthread_join(data->ph[i]->t_id, NULL);
		i++;
	}
}
