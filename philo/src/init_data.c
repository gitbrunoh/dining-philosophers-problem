/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:13:44 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/12 15:09:04 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_keydata_allocs(t_keydata **keydata)
{
	(*keydata)->forks = malloc(sizeof(pthread_mutex_t) \
	* (*keydata)->nbr_philos);
	if ((*keydata)->forks == NULL)
	{
		free(*keydata);
		free(keydata);
		printf("Error: Malloc failed\n");
		return (ERROR);
	}
	(*keydata)->philos = malloc(sizeof(t_philo) * (*keydata)->nbr_philos);
	if ((*keydata)->philos == NULL)
	{
		free((*keydata)->forks);
		free(*keydata);
		free(keydata);
		printf("Error: Malloc failed\n");
		return (ERROR);
	}
	return (SUCCESS);
}

static void	ft_set_keydata(t_keydata **keydata, int argc, char **argv)
{
	if (argc == 6)
		(*keydata)->nbr_meals = ft_atoi(argv[5]);
	else
		(*keydata)->nbr_meals = -1;
	(*keydata)->nbr_philos = ft_atoi(argv[1]);
	(*keydata)->time_to_die = ft_atoi(argv[2]);
	(*keydata)->time_to_eat = ft_atoi(argv[3]);
	(*keydata)->time_to_sleep = ft_atoi(argv[4]);
	(*keydata)->game_start_time = 0;
	(*keydata)->died = false;
	(*keydata)->all_meals = false;
	(*keydata)->sinc_start_flag = false;
}

void	ft_set_philos(t_keydata **keydata)
{
	int	i;

	i = 0;
	while (i < (*keydata)->nbr_philos)
	{
		(*keydata)->philos[i].id = i;
		(*keydata)->philos[i].left_fork_id = i;
		(*keydata)->philos[i].right_fork_id = i + 1;
		if (i == (*keydata)->nbr_philos - 1)
			(*keydata)->philos[i].right_fork_id = 0;
		(*keydata)->philos[i].meals_eaten = 0;
		(*keydata)->philos[i].last_meal_start = 0;
		(*keydata)->philos[i].keydata = *keydata;
		i++;
	}
}

int	ft_init_data(t_keydata **keydata, int argc, char **argv)
{
	*keydata = malloc(sizeof(t_keydata));
	if (keydata == NULL)
	{
		printf("Error: Malloc failed\n");
		return (ERROR);
	}
	ft_set_keydata(keydata, argc, argv);
	if (ft_keydata_allocs(keydata) == ERROR)
		return (ERROR);
	ft_set_philos(keydata);
	return (SUCCESS);
}
