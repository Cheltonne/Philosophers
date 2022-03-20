/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajax <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:40:57 by chajax            #+#    #+#             */
/*   Updated: 2022/03/20 17:58:26 by chajax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_fct(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->id % 2 == 0)
		smart_sleep(philo->shared->tte, philo);
	while (ph_is_dead(philo) == FALSE)
	{
		pthread_create(&philo->death_id, NULL, &check_death, philo);
		routine(philo);
		pthread_detach(philo->death_id);
		if (philo->shared->total_meals != 0)
			all_meals_done(philo);
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
	pthread_mutex_unlock(philo->r_f);
	pthread_mutex_unlock(&philo->l_f);
	sleep_think(philo);
}

int	parsing(int ac, char **av)
{
	int		i;
	size_t	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (j < ft_strlen(av[i]))
		{
			if (ft_isdigit(av[i][j]))
				j++;
			else
				return (0);
		}
		if (ft_atoi(av[i]) < 1 || ft_atoi(av[i]) > INT_MAX)
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
		return (0);
	}
	ft_putstr_fd(
		"This program should take 4 or 5 arguments, and all should be", 2);
	ft_putstr_fd(
		" positive INT type values =! 0. Thank you for your patience.\n", 2);
	return (1);
}
