/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:40:46 by chajax            #+#    #+#             */
/*   Updated: 2022/03/01 17:57:16 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *add_philo(t_data *data, int id)
{
	t_philo	*ret;

	ret = malloc(sizeof(t_philo));
	if (!ret)
		return (NULL);
	pthread_create(&ret->t_id, NULL, &routine, data);
	ret->id = id;
	pthread_mutex_init(&ret->l_f, NULL);
	if (id == data->total_ph)
		ret->r_f = &data->ph[0]->l_f;
	else
		ret->r_f = &data->ph[id]->l_f;
	return (ret);
}

void	init_ph(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->total_ph)
	{
		data->ph[i] = add_philo(data, i + 1);
		i++;
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	data->av = av;
	data->ac = ac;
	data->total_ph = ft_atoi(av[1]);
	data->ttd = ft_atoi(av[2]);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	if (av[5])
		data->m_e = ft_atoi(av[5]);
	data->ph = malloc(sizeof(t_philo *) * data->total_ph);
	if (data->ph == NULL)
		return ;
}
