/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zal-qais <zal-qais@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:59:23 by zal-qais          #+#    #+#             */
/*   Updated: 2025/09/01 17:11:43 by zal-qais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_philo_number(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_content(argv[1]) == 1)
	{
		write(2, "Invalid philosophers number\n", 29);
		return (1);
	}
	return (0);
}

int	check_valid_args(char **argv)
{
	if (check_philo_number(argv) == 1)
		return (1);
	if (ft_atoi(argv[2]) <= 0 || check_content(argv[2]) == 1)
	{
		write(2, "Invalid time to die\n", 21);
		return (1);
	}
	if (ft_atoi(argv[3]) <= 0 || check_content(argv[3]) == 1)
	{
		write(2, "Invalid time to eat\n", 21);
		return (1);
	}
	if (ft_atoi(argv[4]) <= 0 || check_content(argv[4]) == 1)
	{
		write(2, "Invalid time to dream\n", 23);
		return (1);
	}
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || check_content(argv[5]) == 1))
	{
		write(2, "Invalid number of times each philosopher must eat\n", 51);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	chopsticks[PHILO_MAX];
	t_table			table;
	t_philo			philos[PHILO_MAX];

	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong argument count\n", 22);
		return (1);
	}
	if (check_valid_args(argv) == 1)
		return (1);
	init_program(&table, philos);
	init_chopsticks(chopsticks, ft_atoi(argv[1]));
	init_philos(philos, &table, chopsticks, argv);
	thread_create(&table, chopsticks);
	freeing(NULL, &table, chopsticks);
	return (0);
}
