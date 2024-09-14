/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:16:00 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/12 15:18:25 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_philos_mutexes(t_keydata *keydata)
{
	int	i;

	i = 0;
	while (i < keydata->nbr_philos)
	{
		if (pthread_mutex_init(&keydata->philos[i].meals_eaten_mutex, NULL) \
		!= 0)
		{
			printf("Error: Mutex initialization failed\n");
			ft_free_destroy(keydata, i - 1, keydata->nbr_philos - 1, i - 1);
			return (ERROR);
		}
		if (pthread_mutex_init(&keydata->philos[i].last_meal_start_mutex, \
		NULL) != 0)
		{
			printf("Error: Mutex initialization failed\n");
			ft_free_destroy(keydata, i, keydata->nbr_philos - 1, i - 1);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

static int	ft_forks_mutexes(t_keydata *keydata)
{
	int	i;

	i = 0;
	while (i < keydata->nbr_philos)
	{
		if (pthread_mutex_init(&keydata->forks[i], NULL) != 0)
		{
			printf("Error: Mutex initialization failed\n");
			ft_free_destroy(keydata, 0, i - 1, 0);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

static int	ft_keydata_mutexes(t_keydata *keydata)
{
	if (pthread_mutex_init(&keydata->print_mutex, NULL) != 0)
	{
		printf("Error: print_mutex initialization failed\n");
		ft_free_allocs(keydata);
		return (ERROR);
	}
	if (pthread_mutex_init(&keydata->died_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&keydata->print_mutex);
		printf("Error: died_mutex initialization failed\n");
		ft_free_allocs(keydata);
		return (ERROR);
	}
	if (pthread_mutex_init(&keydata->all_meals_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&keydata->print_mutex);
		pthread_mutex_destroy(&keydata->died_mutex);
		printf("Error: all_meals_mutex initialization failed\n");
		ft_free_allocs(keydata);
		return (ERROR);
	}
	if (ft_forks_mutexes(keydata) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ft_init_mutexes(t_keydata *keydata)
{
	if (ft_keydata_mutexes(keydata) == ERROR)
		return (ERROR);
	if (ft_philos_mutexes(keydata) == ERROR)
		return (ERROR);
	if (pthread_mutex_init(&keydata->sinc_start_mutex, NULL) != 0)
	{
		printf("Error: sinc_start_mutex initialization failed\n");
		ft_free_destroy(keydata, keydata->nbr_philos - 1, \
		keydata->nbr_philos - 1, keydata->nbr_philos - 1);
		return (ERROR);
	}
	return (SUCCESS);
}
