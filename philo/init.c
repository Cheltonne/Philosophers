/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:40:46 by chajax            #+#    #+#             */
/*   Updated: 2022/03/04 19:10:06 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *add_philo(t_shared *data, int id)
{
	t_philo	*ret;

	ret = malloc(sizeof(t_philo));
	if (!ret)
		return (NULL);
	ret->id = id;
	pthread_mutex_init(&ret->l_f, NULL);
	if (id == data->total_ph)
		ret->r_f = &data->ph[0]->l_f;
	else
		ret->r_f = &data->ph[id + 1]->l_f;
	ret->shared = data;
	return (ret);
}

void	init_ph(t_shared *data)
{
	int	i;

	i = 0;
	while(i < data->total_ph)
	{
		data->ph[i] = add_philo(data, i + 1);
		i++;
	}
	i = 0;
	while(i < data->total_ph)
	{
		pthread_create(&data->ph[i]->t_id, NULL, &routine, data->ph[i]);
		i++;
	}
	i = 0;
	while(i < data->total_ph)
	{
		pthread_join(data->ph[i]->t_id, NULL);
		i++;
	}
}

void	init_shared(t_shared *data, int ac, char **av)
{
	data->ph = malloc(sizeof(t_philo *) * ft_atoi(av[1]));
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
	pthread_mutex_init(&data->write_m, NULL);
}
