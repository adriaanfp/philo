/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 12:17:11 by aflores-          #+#    #+#             */
/*   Updated: 2025-05-15 12:17:11 by aflores-         ###   ########aflores-  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    parse_args(int ac, char **av, t_rules *rules)
{
    if (ac != 5 && ac != 6)
    {
        printf("Error: invalid number of arguments\n");
        return 0;
    }
    if (!safe_atol(av[1], &rules->nb_philo)
        || !safe_atol(av[2], &rules->time_to_die)
        || !safe_atol(av[3], &rules->time_to_eat)
        || !safe_atol(av[4], &rules->time_to_sleep)
        || (ac == 6 && !safe_atol(av[5], &rules->must_eat)))
    {
        printf("Error: invalid or out-of-range argument(s)\n");
        return 0;
    }
    if (rules->nb_philo < 0 || rules->nb_philo > 200)
    {
        printf("Error: number of philosophers must be between 1 and 200\n");
        return 0;
    }
    if (ac == 5)
        rules->must_eat = -1;
    return 1;
}

static void setup_philo(t_rules *rules, int i)
{
    rules->philos[i].id = i + 1;
	rules->philos[i].meals_eaten = 0;
	rules->philos[i].last_meal = 0;
	rules->philos[i].rules = rules;
	rules->philos[i].left_fork = &rules->forks[i];
	if (i == rules->nb_philo - 1)
		rules->philos[i].right_fork = &rules->forks[0];
	else
		rules->philos[i].right_fork = &rules->forks[i + 1];
}

int init_philo(t_rules *rules)
{
    int i;

    i = 0;
    while (i < rules->nb_philo)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
        {
            printf("Error: mutex init failed for fork %d\n", i);
			return (0);
        }
        i++;
    }
    if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
    {
        printf("Error initializing print mutex\n");
        return (0);
    }
    i = 0;
    while (i < rules->nb_philo)
    {
        setup_philo(rules, i);
        i++;
    }
    return 1;
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	(void)argc;
	(void)argv;

	// Hardcodeamos los valores para probar
	rules.nb_philo = 5;
	rules.time_to_die = 800;
	rules.time_to_eat = 200;
	rules.time_to_sleep = 200;
	rules.must_eat = -1;

	if (!init_memory(&rules))
		return (1);
	if (!init_philo(&rules))
	{
		free_memory(&rules);
		return (1);
	}
    if (!start_threads(&rules))
    {
	free_memory(&rules);
	return (1);
    }
	// Probar salida
	printf("Initialized %d philosophers:\n", rules.nb_philo);
	int i = 0;
	while (i < rules.nb_philo)
	{
		pthread_join(rules.philos[i].thread_id, NULL);
        i++;
	}
	// Liberar recursos
	free_memory(&rules);
	return (0);
}
