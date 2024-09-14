/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:02:24 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/11 19:00:28 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_check_nbr_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	ft_check_args(char **argv)
{
	int	i;
	int	nbr;

	i = 1;
	while (argv[i])
	{
		nbr = ft_atoi(argv[i]);
		if (nbr == -1)
			return (ERROR);
		if (nbr < 0 || nbr == 0)
		{
			printf("Error: Wrong argument\n");
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

static int	ft_check_nbr_philos(char *arg)
{
	if (ft_atoi(arg) == -1)
	{
		return (ERROR);
	}
	if (ft_atoi(arg) > 200 || ft_atoi(arg) == 0)
	{
		printf("Error: Wrong number of philosophers\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_args_validation(int argc, char **argv)
{
	if (ft_check_nbr_args(argc) == ERROR)
		return (ERROR);
	if (ft_check_nbr_philos(argv[1]) == ERROR)
		return (ERROR);
	if (ft_check_args(argv) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
