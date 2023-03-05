/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:19:35 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/05 13:19:40 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meal_eated;
	long			last_meal;
	pthread_t		death;
	struct s_main	*main;
}					t_philo;

typedef struct s_main
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_mealls;
	int				number_of_philos;
	int				is_died;
	int				all_eat;
	long			start_time;
	t_philo			*philo;
	sem_t			*forks;
	sem_t			*died;
}					t_main;

void				init_main(t_main *args, char **av);
void				start_thread(t_main *args);
void				*task(t_philo *philo);
long				current_time(void);
void				picking(t_philo *philo);
void				better_usleep(t_main *args, int bar);
void				*is_dead(void *phil);
int					ft_atoi(const char *str);
void				print_task(t_main *args, char *a, int i);
int					check_positive(char **a);
void				wait_chillds(t_main *args, int *tabel_id);

#endif