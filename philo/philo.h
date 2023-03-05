/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:00:21 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/05 13:19:45 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				fork_left;
	int				fork_right;
	int				meal_eated;
	long			last_meal;
	pthread_t		number_of_philo;
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	decalre;
}					t_main;

void				picking(t_philo *philo);
int					ft_atoi(char *str);
long				current_time(void);
int					init_main(t_main *args, char **av);
void				print_task(t_main *args, char *a, int i);
void				is_dead(t_philo *philo, t_main *args);
int					check_positive(char **a);
int					start_thread(t_main *args);
void				*task(void *i);
void				better_usleep(t_main *args, int bar);
void				check_deads(t_main *args);
void				join_threads(t_main *args);
void				check_all_eated(t_main *args);
void				init_argument(t_main *args, char **av);

#endif