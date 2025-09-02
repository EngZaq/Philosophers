/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:06:26 by zal-qais          #+#    #+#             */
/*   Updated: 2025/09/02 16:07:31 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->l_chopstick < philo->r_chopstick)
	{
		first = philo->l_chopstick;
		second = philo->r_chopstick;
	}
	else
	{
		first = philo->r_chopstick;
		second = philo->l_chopstick;
	}
	pthread_mutex_lock(first);
	print_message("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(first);
		return (0);
	}
	pthread_mutex_lock(second);
	print_message("has taken a fork", philo, philo->id);
	return (1);
}

void	perform_eat(t_philo *philo)
{
	size_t	eat_start;

	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	philo->eating = 1;
	pthread_mutex_unlock(philo->meal_lock);
	print_message("is eating", philo, philo->id);
	eat_start = get_current_time();
	while ((get_current_time() - eat_start) < philo->time_to_eat)
		usleep(100);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->l_chopstick < philo->r_chopstick)
	{
		first = philo->l_chopstick;
		second = philo->r_chopstick;
	}
	else
	{
		first = philo->r_chopstick;
		second = philo->l_chopstick;
	}
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return ;
	perform_eat(philo);
	put_forks(philo);
}
