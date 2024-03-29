/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:20:21 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/14 15:41:58 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//PRINT WHAT PHILOS ARE DOING
void	print_task(t_main *args, char *a, int i)
{
	pthread_mutex_lock(&args->decalre);
	if (!args->is_died && !args->all_eat)
		printf("%lld %d %s\n", (current_time() - args->start_time), i, a);
	pthread_mutex_unlock(&args->decalre);
}

//CHECK IF ALL EATED
void	check_all_eated(t_main *args)
{
	int	i;

	i = -1;
	while (++i < args->number_of_philos)
	{
		pthread_mutex_lock(&args->eating[i]);
		if (args->philo[i].meal_eated < args->number_of_mealls)
		{
			pthread_mutex_unlock(&args->eating[i]);
			return ;
		}
		pthread_mutex_unlock(&args->eating[i]);
	}
	pthread_mutex_lock(&args->decalre);
	args->all_eat = 1;
	pthread_mutex_unlock(&args->decalre);
}

//TIME COUNTER
long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//THREAD WORK
void	*task(void *i)
{
	t_philo	*philo;
	t_main	*args;

	philo = (t_philo *)i;
	args = philo->main;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (!is_died(args, 0) && !(args->all_eat))
	{
		picking(philo);
		print_task(args, "is sleeping", philo->id);
		better_usleep(args->time_to_sleep);
		print_task(args, "is thinking", philo->id);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_main	*args;

	if (ac == 5 || ac == 6)
	{
		if (!check_positive(av))
			return (0);
		args = malloc(sizeof(t_main));
		if (!args)
			return (0);
		if (!init_main(args, av))
		{
			free(args);
			return (0);
		}
		if (!start_thread(args))
			return (1);
		check_deads(args);
		join_threads(args);
	}
	return (1);
}
