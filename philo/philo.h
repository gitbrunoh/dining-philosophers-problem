/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:20:10 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/12 17:30:16 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>

# define SUCCESS 0
# define ERROR 1

typedef struct s_philo
{
	int					id;
	int					right_fork_id; // Id of the philosopher's right fork.
	int					left_fork_id; // Id of the philosopher's left fork.
	int					meals_eaten; // Nbr of meals eaten by the philo
	time_t				last_meal_start; // Time when the last meal started
	pthread_t			thread_id; // Thread id of the philosopher
	pthread_mutex_t		meals_eaten_mutex; // Mutex for the meals_eaten var
	pthread_mutex_t		last_meal_start_mutex; // Mutex for the last_meal_start
	struct s_keydata	*keydata;
}					t_philo;

typedef struct s_keydata
{
	int				nbr_meals; // Selected by the user by argv[5] and const
	int				nbr_philos; // Selected by the user by argv[1] and const
	time_t			time_to_die; // Selected by the user by argv[2] and const
	time_t			time_to_eat; // Selected by the user by argv[3] and const
	time_t			time_to_sleep; // Selected by the user by argv[4] and const
	time_t			game_start_time; // Time when the game starts
	bool			died; // 1 if a philo died
	bool			all_meals; // 1 if all the philos have eaten the nbr_meals
	bool			sinc_start_flag;
	pthread_mutex_t	sinc_start_mutex; // Mutex for the game_start_time
	pthread_mutex_t	*forks; // Array of mutexes for the forks
	pthread_mutex_t	died_mutex; // Mutex for the died variable
	pthread_mutex_t	all_meals_mutex; // Mutex for the all_meals variable
	pthread_mutex_t	print_mutex; // Mutex for all the print functions
	t_philo			*philos; // Array of philos
}					t_keydata;

// INPUTS (ARGV) VALIDATION
int		ft_atoi(const char *nptr);
int		ft_args_validation(int argc, char **argv);

// INITIALIZATION
int		ft_init_data(t_keydata **keydata, int argc, char **argv);
int		ft_init_mutexes(t_keydata *keydata);

// ERROR AND EXIT HANDLING
void	ft_free_destroy(t_keydata *keydata, int i, int i_forks, \
int i_last_meal);
void	ft_end_program(t_keydata *keydata);
void	ft_free_allocs(t_keydata *keydata);

// UTILS
time_t	ft_get_time(void);
void	int_to_str(char *str, int n);
void	ft_strcat(char *dest, const char *src);
void	ft_strcpy(char *dest, const char *src);
int		ft_strlen(const char *str);

// THREADS
void	ft_threads(t_keydata *keydata);

// PRINT
void	ft_print_fork(t_keydata *keydata, int philo_id);
void	ft_print_dead(t_keydata *keydata, int philo_id);
void	ft_printset_eat(t_keydata *keydata, t_philo *philo);
void	ft_print_sleep(t_keydata *keydata, int philo_id);
void	ft_print_thinking(t_keydata *keydata, int philo_id);

// LIFE OF A PHILOSOPHER
void	ft_sleeping(t_keydata *keydata);
void	ft_handle_eating(t_philo *philo, t_keydata *keydata);
void	ft_pick_forks(t_keydata *keydata, t_philo *philo);

// THREADS (PHILOSOPHERS) FT_PHILOROPHERS
void	*ft_philosophers(void *arg);

// CHECKS
int		ft_check_allmeals(t_keydata *keydata);
int		ft_check_starvation(t_keydata *keydata);
int		ft_check_gameover(t_keydata *keydata);

// GETTERS
bool	ft_get_died(t_keydata *keydata);
bool	ft_get_allmeals(t_keydata *keydata);

#endif