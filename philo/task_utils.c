/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:37:51 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/14 11:45:41 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// CHECK IF A PHILO DIED
void	is_dead(t_philo *philo, t_main *args)
{
	int		i;
	long	time;

	i = -1;
	while (++i < args->number_of_philos)
	{
		pthread_mutex_lock(&args->time[i]);
		time = (current_time() - philo[i].last_meal);
		pthread_mutex_unlock(&args->time[i]);
		if (time >= args->time_to_die)
		{
			print_task(args, "died", i + 1);
			is_died(args, 1);
		}
	}
}

// MY PERSONAL USLEEP
void	better_usleep(int bar)
{
	long	i;

	i = current_time();
	while (1)
	{
		if (current_time() - i >= bar)
			break ;
		usleep(50);
	}
}

// CHECK PHILOS STATUS
void	check_deads(t_main *args)
{
	while (!(args->is_died) && !(args->all_eat))
	{
		is_dead(args->philo, args);
		if (args->number_of_mealls > 0)
			check_all_eated(args);
	}
}

// WAIT FOR PHILOS TO FINISH AND FREE ARGUMENT
void	join_threads(t_main *args)
{
	int	i;

	i = -1;
	while (++i < args->number_of_philos)
	{
		if (pthread_join(args->philo[i].number_of_philo, NULL))
			return ;
	}
	i = 0;
	while (i < args->number_of_philos)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&args->eating[i]);
		pthread_mutex_destroy(&args->time[i]);
		i++;
	}
	pthread_mutex_destroy(&args->decalre);
	free(args->philo);
	free(args->forks);
	free(args);
}

//INIT ARGUMENT
void	init_argument(t_main *args, char **av)
{
	args->number_of_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->is_died = 0;
	args->all_eat = 0;
	args->start_time = current_time();
	if (av[5] != 0)
		args->number_of_mealls = ft_atoi(av[5]);
	else
		args->number_of_mealls = -1;
}
