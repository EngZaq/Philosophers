#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_chopstick;
	pthread_mutex_t	*l_chopstick;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;
typedef struct s_table
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_table;

void				freeing(char *str, t_table *table,
						pthread_mutex_t *chopsticks);
void				init_program(t_table *table, t_philo *philos);
void				init_chopsticks(pthread_mutex_t *chopsticks, int philo_num);
void				init_philos(t_philo *philos, t_table *table,
						pthread_mutex_t *chopsticks, char **argv);
void				init_input(t_philo *philo, char **argv);
void				*monitor(void *pointer);
void				*philo_routine(void *pointer);
void				eat(t_philo *philo);
void				dream(t_philo *philo);
void				think(t_philo *philo);
int					check_valid_args(char **argv);
int					check_content(char *arg);
int					thread_create(t_table *table, pthread_mutex_t *chopsticks);
int					dead_loop(t_philo *philo);
int					check_if_all_ate(t_philo *philos);
int					check_if_dead(t_philo *philos);
int					philosopher_dead(t_philo *philo, size_t time_to_die);
int					ft_atoi(char *str);
int					ft_usleep(size_t microseconds);
int					ft_strlen(char *str);
void				print_message(char *str, t_philo *philo, int id);
size_t				get_current_time(void);

#endif
