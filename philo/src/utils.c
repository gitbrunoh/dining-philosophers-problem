/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:18:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/11 18:59:28 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	reverse_str(char *str)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = ft_strlen(str) - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

void	int_to_str(char *str, int n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		str[i] = '0';
		str[i + 1] = '\0';
		return ;
	}
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	str[i] = '\0';
	reverse_str(str);
}

static int	is_space(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	else
		return (0);
}

static int	check_digits(const char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			printf("Error: Wrong argument\n");
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_atoi(const char *arg)
{
	int	nbr;

	nbr = 0;
	while (is_space(*arg) == 1)
		arg++;
	if (check_digits(arg) == ERROR)
		return (nbr);
	while (*arg >= '0' && *arg <= '9')
	{
		if (nbr > (INT_MAX - (*arg - '0')) / 10)
		{
			printf("Error: Overflow: Out-of-range argument\n");
			return (-1);
		}
		nbr = nbr * 10 + (*arg - '0');
		arg++;
	}
	return (nbr);
}
