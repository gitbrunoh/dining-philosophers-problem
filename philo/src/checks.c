/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:18:36 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/11 12:49:21 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_gameover(t_keydata *keydata)
{
	if (ft_get_died(keydata))
		return (1);
	if (ft_get_allmeals(keydata))
		return (1);
	return (0);
}

int	ft_check_starvation(t_keydata *keydata)
{
	int		i;
	time_t	last_meal_start;

	i = 0;
	while (i < keydata->nbr_philos)
	{
		pthread_mutex_lock(&keydata->philos[i].last_meal_start_mutex);
		last_meal_start = keydata->philos[i].last_meal_start;
		pthread_mutex_unlock(&keydata->philos[i].last_meal_start_mutex);
		if ((ft_get_time() - last_meal_start) >= keydata->time_to_die)
		{
			pthread_mutex_lock(&keydata->died_mutex);
			if (!keydata->died)
			{
				keydata->died = 1;
				pthread_mutex_unlock(&keydata->died_mutex);
				ft_print_dead(keydata, keydata->philos[i].id);
			}
			else
				pthread_mutex_unlock(&keydata->died_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_allmeals(t_keydata *keydata)
{
	int	i;

	i = 0;
	while (i < keydata->nbr_philos)
	{
		pthread_mutex_lock(&keydata->philos[i].meals_eaten_mutex);
		if (keydata->philos[i].meals_eaten < keydata->nbr_meals)
		{
			pthread_mutex_unlock(&keydata->philos[i].meals_eaten_mutex);
			return (0);
		}
		pthread_mutex_unlock(&keydata->philos[i].meals_eaten_mutex);
		i++;
	}
	pthread_mutex_lock(&keydata->all_meals_mutex);
	keydata->all_meals = 1;
	pthread_mutex_unlock(&keydata->all_meals_mutex);
	return (1);
}
