/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:27:46 by brunhenr          #+#    #+#             */
/*   Updated: 2024/09/11 22:43:30 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_thinking(t_keydata *keydata, int philo_id)
{
	time_t	current_time;
	long	elapsed_time;
	char	buffer[100];
	char	temp[50];
	int		len;

	current_time = ft_get_time();
	elapsed_time = current_time - keydata->game_start_time;
	int_to_str(temp, elapsed_time);
	strcpy(buffer, temp);
	ft_strcat(buffer, " ");
	int_to_str(temp, philo_id + 1);
	ft_strcat(buffer, temp);
	ft_strcat(buffer, " is thinking\n");
	len = strlen(buffer);
	pthread_mutex_lock(&keydata->print_mutex);
	if (!ft_check_gameover(keydata))
		write(1, buffer, len);
	pthread_mutex_unlock(&keydata->print_mutex);
	if (keydata->nbr_philos % 2)
		usleep(5000);
}

void	ft_print_sleep(t_keydata *keydata, int philo_id)
{
	time_t	current_time;
	long	elapsed_time;
	char	buffer[100];
	char	temp[50];
	int		len;

	current_time = ft_get_time();
	elapsed_time = current_time - keydata->game_start_time;
	int_to_str(temp, elapsed_time);
	strcpy(buffer, temp);
	ft_strcat(buffer, " ");
	int_to_str(temp, philo_id + 1);
	ft_strcat(buffer, temp);
	ft_strcat(buffer, " is sleeping\n");
	len = strlen(buffer);
	pthread_mutex_lock(&keydata->print_mutex);
	if (!ft_check_gameover(keydata))
		write(1, buffer, len);
	pthread_mutex_unlock(&keydata->print_mutex);
}

void	ft_printset_eat(t_keydata *keydata, t_philo *philo)
{
	time_t	current_time;
	long	elapsed_time;
	char	buffer[100];
	char	temp[50];
	int		len;

	current_time = ft_get_time();
	elapsed_time = current_time - keydata->game_start_time;
	int_to_str(temp, elapsed_time);
	strcpy(buffer, temp);
	ft_strcat(buffer, " ");
	int_to_str(temp, philo->id + 1);
	ft_strcat(buffer, temp);
	ft_strcat(buffer, " is eating\n");
	len = strlen(buffer);
	pthread_mutex_lock(&philo->last_meal_start_mutex);
	philo->last_meal_start = current_time;
	pthread_mutex_unlock(&philo->last_meal_start_mutex);
	pthread_mutex_lock(&keydata->print_mutex);
	if (!ft_check_gameover(keydata))
		write(1, buffer, len);
	pthread_mutex_unlock(&keydata->print_mutex);
}

void	ft_print_fork(t_keydata *keydata, int philo_id)
{
	time_t	current_time;
	long	elapsed_time;
	char	buffer[100];
	char	temp[50];
	int		len;

	current_time = ft_get_time();
	elapsed_time = current_time - keydata->game_start_time;
	int_to_str(temp, elapsed_time);
	strcpy(buffer, temp);
	ft_strcat(buffer, " ");
	int_to_str(temp, philo_id + 1);
	ft_strcat(buffer, temp);
	ft_strcat(buffer, " has taken a fork\n");
	len = strlen(buffer);
	pthread_mutex_lock(&keydata->print_mutex);
	if (!ft_check_gameover(keydata))
		write(1, buffer, len);
	pthread_mutex_unlock(&keydata->print_mutex);
}

void	ft_print_dead(t_keydata *keydata, int philo_id)
{
	time_t	current_time;
	long	elapsed_time;
	char	buffer[100];
	char	temp[50];
	int		len;

	current_time = ft_get_time();
	elapsed_time = current_time - keydata->game_start_time;
	int_to_str(temp, elapsed_time);
	strcpy(buffer, temp);
	ft_strcat(buffer, " ");
	int_to_str(temp, philo_id + 1);
	ft_strcat(buffer, temp);
	ft_strcat(buffer, " died\n");
	len = strlen(buffer);
	pthread_mutex_lock(&keydata->print_mutex);
	write(1, buffer, len);
	pthread_mutex_unlock(&keydata->print_mutex);
}
