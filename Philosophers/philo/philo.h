/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:41:04 by asebban           #+#    #+#             */
/*   Updated: 2025/06/01 12:24:42 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

# define YELLOW  "\033[1;33m"
# define RED "\033[1;31m"
# define RESET   "\033[0m"
# define BLUE    "\033[1;34m"

typedef struct s_info	t_info;
typedef struct s_philo
{
	size_t				id;
	pthread_t			thread;
	int					meals_eaten;
	long long			last_meal_time;
	int					is_eating;
	int					left_fork;
	int					right_fork;
	t_info				*info;
}	t_philo;

typedef struct s_info
{
	int				numbers_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_died;
	int				all_ate;
	long long		time_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	death_lock;
	t_philo			*philos;
}	t_info;

int			err(char *str);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		ft_usage(void);
void		ft_clean(t_info *info);
int			init_philos(t_info *info);
int			init_mutexes(t_info *info);
long long	get_time_start(void);
void		print_status(t_philo *philo, char *str);
void		*philo_routine(void *arg);
void		smart_sleep(long long time, t_philo *philo);
int			check_all_ate(t_info *info);
int			check_death(t_philo *philo, t_info *info);
t_info		*alloc_info(void);
void		*monitor(void *arg);
void		one_philo(t_philo *philo);
void		think(t_philo *philo);
void		drop_forks(t_philo *philo);
void		eat(t_philo *philo);
void		take_forks(t_philo *philo);
bool		check_death1(t_philo *philo);

#endif