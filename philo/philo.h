/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:45:31 by psimarro          #+#    #+#             */
/*   Updated: 2024/01/09 21:15:34 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

struct s_program;

typedef struct s_philo
{
	int					id;
	int					n_eats; // number of times a philo has eaten
	time_t				t_start;
	time_t				t_last_eat;
	int					*fork[2];
	struct s_program	*program;
	pthread_mutex_t		right_lock;
	pthread_mutex_t		*left_lock;
	pthread_mutex_t		*full_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		*dead_mutex;
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
    pthread_mutex_t	write_lock;
    pthread_mutex_t	dead_mutex;
    pthread_mutex_t	full_mutex;
    t_philo			**philos;
}				t_program;

/* INIT.C */
t_program   parse_input(int argc, char **argv);
t_philo		**init_philos(t_program  *program);

/* LAUNCH.C */
int			launcher(t_program *program);
void		*routine(void *data);

/* FT_PATOI.C */
int			ft_patoi(const char *str);

/* UTILS.C */
int			check_err(t_program *program, int argc);
int			ft_perror(char *str);
time_t		ft_time(void);


#endif
