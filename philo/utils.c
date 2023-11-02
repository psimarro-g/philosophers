/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:56:17 by psimarro          #+#    #+#             */
/*   Updated: 2023/11/02 11:41:03 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

//get time in miliseconds
time_t	ft_time(void)
{
	struct timeval	time;
	time_t				ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

void	check_err(t_program *program, int argc)
{
	if (program->n_philo < 1|| program->t_die < 0 || program->t_eat < 0
		|| program->t_sleep < 0)
	{
		printf("Error: negative values\n");
		exit(1);
	}
	if (argc == 6 && program->n_eat <= 0)
	{
		printf("Error: n_eat can't be <= 0\n");
		exit(1);
	}
}