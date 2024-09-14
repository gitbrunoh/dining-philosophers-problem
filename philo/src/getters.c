/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:25:27 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/09 22:22:07 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	ft_get_allmeals(t_keydata *keydata)
{
	bool	all_meals;

	pthread_mutex_lock(&keydata->all_meals_mutex);
	all_meals = keydata->all_meals;
	pthread_mutex_unlock(&keydata->all_meals_mutex);
	return (all_meals);
}

bool	ft_get_died(t_keydata *keydata)
{
	bool	died;

	pthread_mutex_lock(&keydata->died_mutex);
	died = keydata->died;
	pthread_mutex_unlock(&keydata->died_mutex);
	return (died);
}
