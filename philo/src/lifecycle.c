/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:24:02 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/15 17:39:50 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_sleeping(t_keydata *keydata)
{
	time_t	start_time;
	time_t	remaining_time;

	start_time = ft_get_time();
	while (!(ft_get_died(keydata)))
	{
		remaining_time = keydata->time_to_sleep - (ft_get_time() - start_time);
		if (remaining_time <= 0.9)
			break ;
		usleep(20);
	}
}

static void	ft_eating(t_keydata *keydata)
{
	time_t	start_time;
	time_t	remaining_time;

	start_time = ft_get_time();
	while (!ft_get_died(keydata))
	{
		remaining_time = keydata->time_to_eat - (ft_get_time() - start_time);
		if (remaining_time <= 0.9)
			break ;
		usleep(20);
	}
}

void	ft_handle_eating(t_philo *philo, t_keydata *keydata)
{
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	ft_printset_eat(keydata, philo);
	ft_eating(keydata);
	pthread_mutex_unlock(&keydata->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&keydata->forks[philo->left_fork_id]);
}

void	ft_pick_forks(t_keydata *keydata, t_philo *philo)
{
	int	first_fork_id;
	int	second_fork_id;

	if (philo->id == keydata->nbr_philos - 1)
	{
		first_fork_id = philo->right_fork_id;
		second_fork_id = philo->left_fork_id;
	}
	else
	{
		first_fork_id = philo->left_fork_id;
		second_fork_id = philo->right_fork_id;
	}
	pthread_mutex_lock(&keydata->forks[first_fork_id]);
	usleep(450);
	ft_print_fork(keydata, (*philo).id);
	pthread_mutex_lock(&keydata->forks[second_fork_id]);
	usleep(450);
	ft_print_fork(keydata, (*philo).id);
}
