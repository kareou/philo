/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:46:20 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/14 16:46:18 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_task(t_main *args, char *a, int i)
{
	sem_wait(args->declare);
	printf("%lld %d %s\n", (current_time() - args->start_time), i, a);
	sem_post(args->declare);
}

void	print_dead(t_main *args, char *a, int i)
{
	if (!args->is_died)
		printf("%lld %d %s\n", (current_time() - args->start_time), i, a);
}

void	*task(t_philo *philo)
{
	t_main	*args;

	args = philo->main;
	if (pthread_create(&philo->death, NULL, &is_dead, philo))
		exit(1);
	while (!(args->is_died))
	{
		picking(philo);
		print_task(args, "is sleeping", philo->id);
		better_usleep(args, args->time_to_sleep);
		print_task(args, "is thinking", philo->id);
	}
	pthread_join(philo->death, NULL);
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
		init_main(args, av);
		init_semphor(args);
		start_thread(args);
		close_sema(args);
		free(args->philo);
	}
	return (1);
}
