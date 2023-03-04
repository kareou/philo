/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:03:07 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/04 17:12:03 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*is_dead(void *phil)
{
	int		i;
	t_philo	*philo;
	t_main	*args;
	long	time;

	philo = (t_philo *)phil;
	args = philo->main;
	i = -1;
	while (!args->is_died && !args->all_eat)
	{
		time = (current_time() - philo->last_meal);
		if (time >= args->time_to_die)
		{
			print_task(args, "died", philo->id);
			args->is_died = 1;
		}
		if (args->number_of_mealls > 0)
		{
			if (philo->meal_eated == args->number_of_mealls)
				args->all_eat = 1;
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

void	wait_chillds(int status, t_main *args, int *id_tabel)
{
	int	i;

	while (!status)
	{
		i = -1;
		while (++i < args->number_of_philos && !status)
			waitpid(id_tabel[i], &status, 0);
	}
	i = -1;
	while (++i < args->number_of_philos)
		kill(id_tabel[i], 9);
	free(id_tabel);
}
