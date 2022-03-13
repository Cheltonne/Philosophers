/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:40:57 by chajax            #+#    #+#             */
/*   Updated: 2022/03/13 15:54:39 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_fct(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->id % 2 == 0)
		smart_sleep(philo->shared->tte * 1000, philo->shared);
	while (philo->shared->ph_dead == FALSE)
	{
		if (philo->shared->total_meals != 0)
		{
			if (philo->shared->done_eating == philo->shared->total_ph)
			{
				pthread_mutex_lock(&philo->shared->write_m);
				if (philo->shared->ph_dead == FALSE)
				{
					printf("%ld ", ms_timeofday() - philo->shared->start_time);
					printf("Everyone has eaten %d times, yay ! o/ \n",
							philo->shared->total_meals);
					philo->shared->ph_dead = TRUE;
				}
				pthread_mutex_unlock(&philo->shared->write_m);
				return (NULL);
			}
		}
		pthread_create(&philo->death_id, NULL, &check_death, philo);
		routine(philo);
		pthread_detach(philo->death_id);
	}
	return (param);
}

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_f);
	pthread_mutex_lock(&philo->shared->write_m);
	print_status("has taken a fork", philo);
	pthread_mutex_unlock(&philo->shared->write_m);
	pthread_mutex_lock(philo->r_f);
	pthread_mutex_lock(&philo->shared->write_m);
	print_status("has taken a fork", philo);
	pthread_mutex_unlock(&philo->shared->write_m);
	eat(philo);
	sleep_think(philo);
	return ;
}

void	*check_death(void *param)
{
	t_philo *philo;

	philo = param;
	smart_sleep(philo->shared->ttd * 1000, philo->shared);
	if ((ms_timeofday() - philo->last_eat) >= philo->shared->ttd)
	{
		pthread_mutex_lock(&philo->shared->death_m);
		pthread_mutex_lock(&philo->shared->write_m);
		print_status("died", philo);
		pthread_mutex_unlock(&philo->shared->write_m);
		philo->shared->ph_dead = TRUE;
		pthread_mutex_unlock(&philo->shared->death_m);
		return (NULL);
	}
	return (NULL);	
}

int	parsing(int ac, char **av)
{
	int	i;
	int j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (ft_isdigit(av[i][j]))
			j++;
		else
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_shared	*data;

	if (parsing(ac, av) && (ac == 5 || ac == 6))
	{
		data = ft_calloc(1, sizeof(t_shared));
		if (data == NULL)
			return (0);
		init_shared(data, ac, av);
		init_ph(data);
		threads(data);
		free_fct(data);
		free(data);
		return (1);
	}
	printf("This program should take 4 or 5 arguments, and all should be numeric values.\n");
}
