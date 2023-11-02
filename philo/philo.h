/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:45:31 by psimarro          #+#    #+#             */
/*   Updated: 2023/11/02 11:42:56 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				n_eats; // number of times a philo has eaten
	time_t			t_start;
	time_t			t_last_eat;
	int				*full; //same for all the philos
	int				*dead; //same for all the philos
	int				*fork[2];
	pthread_mutex_t	*right_lock;
	pthread_mutex_t	*left_lock;
	pthread_mutex_t	*full_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*dead_mutex;

}				t_philo;

typedef struct s_program
{
    int				n_philo;
    int				t_die;
    int				t_eat;
    int				t_sleep;
    time_t			t_start;
    int				n_eat;
    int				dead;
	int				full;
    pthread_mutex_t	*write_lock;
    pthread_mutex_t	dead_mutex;
    pthread_mutex_t	full_mutex;
    t_philo			**philos;
}				t_program;

/* FT_PATOI.C */
int	    ft_ptr_atoi(const char *str);

/* UTILS.C */
void	check_err(t_program *program, int argc);
void	ft_error(char *str);
time_t	ft_time(void);

#endif
