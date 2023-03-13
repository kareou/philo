/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:36:51 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/12 14:17:18 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//PHILOS ARE EATING
void	picking(t_philo *philo)
{
	t_main	*args;

	args = philo->main;
	pthread_mutex_lock(&args->forks[philo->fork_left]);
	print_task(args, "has taken a fork", philo->id);
	if (args->number_of_philos == 1)
	{
		better_usleep(args->time_to_die);
		return ;
	}
	pthread_mutex_lock(&args->forks[philo->fork_right]);
	print_task(args, "has taken a fork", philo->id);
	print_task(args, "is eating", philo->id);
	pthread_mutex_lock(&args->time[philo->id - 1]);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&args->time[philo->id - 1]);
	philo->meal_eated++;
	better_usleep(args->time_to_eat);
	pthread_mutex_unlock(&args->forks[philo->fork_left]);
	pthread_mutex_unlock(&args->forks[philo->fork_right]);
}

//ATOI
int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str && str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10;
		res = res + str[i] - 48;
		i++;
	}
	return (res * sign);
}

//CHECK IF ARGUMENT ARE OK
int	check_positive(char **a)
{
	int	i;

	i = 1;
	while (a[i])
	{
		if (ft_atoi(a[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

//INIT ARGUMENT AND ALLOC
int	init_main(t_main *args, char **av)
{
	int	i;

	args->philo = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	if (!args->philo)
		return (0);
	args->forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	if (!args->forks)
		return (0);
	args->time = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	if (!args->time)
		return (0);
	init_argument(args, av);
	if (pthread_mutex_init(&args->decalre, NULL))
		return (0);
	i = -1;
	while (++i < args->number_of_philos)
	{
		if (pthread_mutex_init(&args->forks[i], NULL))
			return (0);
		if (pthread_mutex_init(&args->time[i], NULL))
			return (0);
	}
	return (1);
}

//START THREAD WORK
int	start_thread(t_main *args)
{
	int	i;

	i = -1;
	while (++i < args->number_of_philos)
	{
		args->philo[i].id = i + 1;
		args->philo[i].fork_left = i;
		args->philo[i].fork_right = (i + 1) % args->number_of_philos;
		args->philo[i].meal_eated = 0;
		args->philo[i].main = args;
		args->philo[i].last_meal = current_time();
		if (pthread_create(&args->philo[i].number_of_philo, NULL, &task,
				&args->philo[i]))
			return (0);
	}
	return (1);
}
