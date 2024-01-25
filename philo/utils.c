/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:56:17 by psimarro          #+#    #+#             */
/*   Updated: 2024/01/25 16:04:54 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"


//get time in miliseconds
time_t	ft_time(void)
{
	struct timeval	time;
	time_t			ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

int	ft_perror(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	check_err(t_program *program, int argc)
{
	if (program->n_philo < 1|| program->t_die < 0 || program->t_eat < 0
		|| program->t_sleep < 0)
		return (ft_perror("Invalid values\nUsage: \
			./philo n_philo t_die t_eat t_sleep [n_eat]"));
	if (argc == 6 && program->n_eat <= 0)
		return (ft_perror("Invalid n_eat\nUsage: \
			./philo n_philo t_die t_eat t_sleep [n_eat]"));
	return (0);
}

void   philo_sleep(time_t time, int *dead)
{
	time_t  start;

	start = ft_time();
	while (!(*dead) && ft_time() - start < time)
		usleep(100);
}

void print_philo_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->program->write_lock);
	if (!philo->program->dead)
		printf("%ld %i %s\n", ft_time() - philo->program->t_start, philo->id, str);
	pthread_mutex_unlock(&philo->program->write_lock);
}