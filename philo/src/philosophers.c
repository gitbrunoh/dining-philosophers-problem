/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:16:51 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/14 19:27:41 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_sinc_start(t_keydata *keydata)
{
	pthread_mutex_lock(&keydata->sinc_start_mutex);
	while (!keydata->sinc_start_flag)
	{
		pthread_mutex_unlock(&keydata->sinc_start_mutex);
		usleep(100);
		pthread_mutex_lock(&keydata->sinc_start_mutex);
	}
	pthread_mutex_unlock(&keydata->sinc_start_mutex);
}

static void	ft_lifecycle(t_philo *philo, t_keydata *keydata)
{
	while (1)
	{
		ft_pick_forks(keydata, philo);
		ft_handle_eating(philo, keydata);
		ft_print_sleep(keydata, philo->id);
		ft_sleeping(keydata);
		ft_print_thinking(keydata, philo->id);
		if (ft_check_gameover(keydata))
			break ;
	}
}

static void	ft_set_last_meal_start(t_philo *philo, t_keydata *keydata)
{
	pthread_mutex_lock(&philo->last_meal_start_mutex);
	philo->last_meal_start = keydata->game_start_time;
	pthread_mutex_unlock(&philo->last_meal_start_mutex);
}

void	*ft_philosophers(void *arg)
{
	t_philo		*philo;
	t_keydata	*keydata;

	philo = (t_philo *)arg;
	keydata = philo->keydata;
	ft_sinc_start(keydata);
	ft_set_last_meal_start(philo, keydata);
	if (philo->id % 2)
		usleep(15000);
	ft_lifecycle(philo, keydata);
	return (NULL);
}
