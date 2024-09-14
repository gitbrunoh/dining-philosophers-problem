/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:57:51 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/12 15:44:34 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_check_envp(char **envp)
{
	if (envp == NULL || envp[0] == NULL)
	{
		printf("Error: No environment variables\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_keydata	*keydata;

	keydata = NULL;
	if (ft_check_envp(envp) == ERROR)
		return (EXIT_FAILURE);
	if (ft_args_validation(argc, argv) == ERROR)
		return (EXIT_FAILURE);
	if (ft_init_data(&keydata, argc, argv) == ERROR)
		return (EXIT_FAILURE);
	if (ft_init_mutexes(keydata) == ERROR)
		return (EXIT_FAILURE);
	ft_threads(keydata);
	ft_end_program(keydata);
	return (EXIT_SUCCESS);
}
