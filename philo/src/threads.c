/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:01:10 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/12 16:50:26 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	ft_game_judge(t_keydata *keydata)
{
	usleep(6000);
	while (!(ft_get_died(keydata)))
	{
		usleep(1000);
		if (ft_check_starvation(keydata))
			return ;
		if (keydata->nbr_meals != -1)
			if (ft_check_allmeals(keydata))
				return ;
	}
}

static void	ft_join_threads(t_keydata *keydata)
{
	int	i;

	i = keydata->nbr_philos;
	if (keydata->nbr_philos == 1)
	{
		pthread_join(keydata->philos[0].thread_id, NULL);
	}
	else
	{
		while (--i >= 0)
			pthread_join(keydata->philos[i].thread_id, NULL);
	}
}

static void	ft_group_dinnig(t_keydata *keydata)
{
	int	i;

	i = 0;
	while (i < keydata->nbr_philos)
	{
		if (pthread_create(&(keydata->philos[i].thread_id), \
		NULL, ft_philosophers, &(keydata->philos[i])) != 0)
		{
			printf("Error: Thread creation failed\n");
			return ;
		}
		i++;
	}
	pthread_mutex_lock(&keydata->sinc_start_mutex);
	keydata->sinc_start_flag = true;
	keydata->game_start_time = ft_get_time();
	pthread_mutex_unlock(&keydata->sinc_start_mutex);
	ft_game_judge(keydata);
}

static void	*ft_alone(void *arg)
{
	t_keydata	*keydata;

	keydata = (t_keydata *)arg;
	ft_print_fork(keydata, keydata->philos[0].id);
	usleep((keydata->time_to_die - \
	(ft_get_time() - keydata-> game_start_time)) * 1000);
	ft_print_dead(keydata, keydata->philos[0].id);
	return (NULL);
}

void	ft_threads(t_keydata *keydata)
{
	keydata->game_start_time = ft_get_time();
	if (keydata->nbr_philos == 1)
	{
		if (pthread_create(&keydata->philos[0].thread_id, \
		NULL, ft_alone, keydata) != 0)
		{
			printf("Error: Thread creation failed\n");
			return ;
		}
	}
	else
		ft_group_dinnig(keydata);
	ft_join_threads(keydata);
	return ;
}
