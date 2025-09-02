/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:13:25 by zal-qais          #+#    #+#             */
/*   Updated: 2025/09/01 16:13:26 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->num_of_philos == 1)
	{
		print_message("has taken a fork", philo, philo->id);
		ft_usleep(philo->time_to_die);
		print_message("died", philo, philo->id);
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		think(philo);
		dream(philo);
	}
	return (NULL);
}

int	thread_create(t_table *table, pthread_mutex_t *chopsticks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, table->philos) != 0)
		freeing("Thread creation error", table, chopsticks);
	i = -1;
	while (++i < table->philos[0].num_of_philos)
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine,
				&table->philos[i]) != 0)
			freeing("Thread creation error", table, chopsticks);
	i = -1;
	if (pthread_join(observer, NULL) != 0)
		freeing("Thread join error", table, chopsticks);
	while (++i < table->philos[0].num_of_philos)
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			freeing("Thread join error", table, chopsticks);
	return (0);
}
