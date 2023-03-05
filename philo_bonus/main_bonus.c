/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:46:20 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/05 12:48:54 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_task(t_main *args, char *a, int i)
{
	if (!args->is_died)
		printf("%ld\t%d\t%s\n", (current_time() - args->start_time), i, a);
}

void	*task(t_philo *philo)
{
	t_main	*args;

	args = philo->main;
	if (philo->id % 2 == 0)
		usleep(1500);
	if (pthread_create(&philo->death, NULL, &is_dead, philo))
		exit(1);
	while (!(args->is_died) && !(args->all_eat))
	{
		picking(philo);
		print_task(args, "is sleeping", philo->id);
		better_usleep(args, args->time_to_sleep);
		print_task(args, "is thinking", philo->id);
	}
	pthread_join(philo->death, NULL);
	exit(1);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_main	*args;

	if (ac < 5)
		return (1);
	if (!check_positive(av))
		return (0);
	args = malloc(sizeof(t_main));
	init_main(args, av);
	sem_unlink("/forks");
	args->forks = sem_open("/forks", O_CREAT, 0777, args->number_of_philos);
	sem_unlink("/died");
	args->died = sem_open("/died", O_CREAT, 0777, 1);
	start_thread(args);
	sem_close(args->forks);
	sem_unlink("/forks");
	sem_close(args->died);
	sem_unlink("/died");
	free(args->philo);
}
