/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:08:14 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/12 15:46:42 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_free_allocs(t_keydata *keydata)
{
	free(keydata->philos);
	free(keydata->forks);
	free(keydata);
}

void	ft_free_destroy(t_keydata *keydata, int i, int i_forks, int i_last_meal)
{
	while (i >= 0)
	{
		if (pthread_mutex_destroy(&keydata->philos[i].meals_eaten_mutex) != 0)
			printf("Error: meals_eaten_mutex destroy failed philo %d\n", i);
		i--;
	}
	while (i_forks >= 0)
	{
		if (pthread_mutex_destroy(&keydata->forks[i_forks]) != 0)
			printf("Error: fork mutex destroy failed for fork: %d\n", i_forks);
		i_forks--;
	}
	while (i_last_meal >= 0)
	{
		if (pthread_mutex_destroy(&keydata->\
		philos[i_last_meal].last_meal_start_mutex) != 0)
			printf("Error: fork mutex destroy failed for fork: %d\n", \
			i_last_meal);
		i_last_meal--;
	}
	pthread_mutex_destroy(&keydata->print_mutex);
	pthread_mutex_destroy(&keydata->died_mutex);
	pthread_mutex_destroy(&keydata->all_meals_mutex);
	ft_free_allocs(keydata);
}

void	ft_end_program(t_keydata *keydata)
{
	pthread_mutex_destroy(&keydata->sinc_start_mutex);
	ft_free_destroy(keydata, keydata->nbr_philos - 1, \
	keydata->nbr_philos - 1, keydata->nbr_philos - 1);
}
