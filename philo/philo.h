/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:45:31 by psimarro          #+#    #+#             */
/*   Updated: 2024/01/25 16:04:00 by psimarro         ###   ########.fr       */
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
	time_t				t_last_eat;
    int				    *fork[2];
	struct s_program	*program;
	pthread_mutex_t		right_lock;
    pthread_mutex_t		eat_mutex;
	pthread_mutex_t		*left_lock;
}				t_philo;

typedef struct s_program
{
    int				n_philo;
    int				t_die;
    int				t_eat;
    int				t_sleep;
    int				n_eat;
    int				dead;
	int				full;
    time_t			t_start;
    pthread_mutex_t	write_lock;
    t_philo			**philos;
}				t_program;

/* INIT.C */
t_program   parse_input(int argc, char **argv);
t_philo		**init_philos(t_program  *program);

/* LAUNCH.C */
int			launcher(t_program *program);
void		*routine(void *data);
void        check_philos(t_program *program);

/* FT_PATOI.C */
int			ft_patoi(const char *str);

/* UTILS.C */
int			check_err(t_program *program, int argc);
int			ft_perror(char *str);
time_t		ft_time(void);
void		philo_sleep(time_t time, int *dead);
void        print_philo_state(t_philo *philo, char *str);


#endif
