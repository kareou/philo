/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:03:07 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/06 12:10:36 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*is_dead(void *phil)
{
	t_philo		*philo;
	t_main		*args;
	long long	time;

	philo = (t_philo *)phil;
	args = philo->main;
	while (!args->is_died && !args->all_eat)
	{
		time = (current_time() - philo->last_meal);
		if (time >= args->time_to_die)
		{
			sem_wait(args->died);
			print_task(args, "died", philo->id);
			exit(1);
		}
		if (args->number_of_mealls > 0 && args->eat_trgr == 0)
		{
			if (philo->meal_eated >= args->number_of_mealls)
			{
				sem_post(args->eat);
				args->eat_trgr = 1;
			}
		}
	}
	return (NULL);
}

void	better_usleep(t_main *args, int bar)
{
	long	i;

	i = current_time();
	while (!(args->is_died))
	{
		if (current_time() - i >= bar)
			break ;
		usleep(50);
	}
}

void	*test(void *b)
{
	t_main	*args;
	int		i;

	i = -1;
	args = (t_main *)b;
	while (++i < args->number_of_philos)
		sem_wait(args->eat);
	i = -1;
	while (++i < args->number_of_philos)
		kill(args->id_tabel[i], 15);
	return (NULL);
}

void	wait_chillds(t_main *args)
{
	int			i;
	pthread_t	tmp;

	i = -1;
	if (args->number_of_mealls > 0)
		pthread_create(&tmp, NULL, test, args);
	waitpid(-1, 0, 0);
	while (++i < args->number_of_philos)
		kill(args->id_tabel[i], 15);
	free(args->id_tabel);
}
