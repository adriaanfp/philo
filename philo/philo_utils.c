/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 12:21:51 by aflores-          #+#    #+#             */
/*   Updated: 2025-05-15 12:21:51 by aflores-         ###   ########aflores-  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_memory(t_rules *rules)
{
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
	{
		printf("Error allocating forks\n");
		return (0);
	}
	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->philos)
	{
		printf("Error allocating philosophers\n");
		free(rules->forks);
		return (0);
	}
	return (1);
}

void	free_memory(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->full_mutex);
	free(rules->forks);
	rules->forks = NULL;
	free(rules->philos);
	rules->philos = NULL;
}

long	get_time(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_ms);
}

int	start_threads(t_rules *rules)
{
	int	i;

	i = 0;
	rules->start_time = get_time();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philos[i].thread_id, NULL, routine,
				&rules->philos[i]) != 0)
		{
			printf("Error creating thread for philosopher %d\n", i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}
