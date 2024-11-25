/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:50:49 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/25 18:06:07 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>          
#include <sys/stat.h>
#include <semaphore.h>
#include <wait.h>
#include <sys/time.h>
#include <signal.h>


#define FORK_SEM_NAME "/unique_fork_sem"
#define PRINT_SEM_NAME "/print_sem"

#define CHILD_PROCESS 0
#define MAX_THREADS 200
#define MAX_USLEEP 1000000

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_RESET "\x1b[0m"

#define MODE_BOLD "\x1b[1m"
#define MODE_DIM "\x1b[2m"
#define MODE_ITALIC "\x1b[3m"
#define MODE_UNDERLINE "\x1b[4m"
#define MODE_BLINKING "\x1b[5m"
#define MODE_REVERSE "\x1b[7m"
#define MODE_STRIKETHROUGH "\x1b[9m"


#define INVALID_PARAM_NUM_MSG "DISASTER! INCORRECT NUMBER OF ARGS\nThis is the paramters I can accept\n1) <number_of_philosophers> \n2) <time_to_die>\n3) <time_to_eat>\n4) <time_to_sleep>\n5) <number_of_times_each_philosopher_must_eat> (optional)\n"
#define MAX_PHILO_ERROR_MSG "Sorry but we don't have that many philosophers in here\nPlease insert a lower number!"
#define ZERO_ERROR "Mmmmh .. We don't like 0 in here, why don't you try with a different number?\n"
#define MAX_USLEEP_ERROR "Woah, that's a big number! Try something smaller, thanks!"

typedef struct s_data
{
    bool                    is_phil_dead;
    int                     how_many_spaghetti;
    int                     philosophers_number;
    __useconds_t            die_time;
    __useconds_t            eat_time;
    __useconds_t            sleep_time;
    size_t                  starting_milliseconds;
    sem_t                   *printing_semaphore;
    sem_t                   *fork_semaphore;
       
}   t_data;


typedef struct s_philosopher
{
    int                     philosopher_num;
    int                     spaghetti_eaten;
    size_t                  last_meal;
    pthread_t               checking_thread;
    t_data                  *data;
    
}   t_philosopher;


//CHECKER FUNCTIONS 

bool            are_args_valid(int argc, char *argv[]);
bool            are_arguments_in_limits(int argc, char *argv[]);

//INIT FUNCTIONS

t_data          *ft_init_data_struct(int argc, char *argv[]);
t_philosopher   *ft_init_philo_struct(t_data *data);


void    start_the_dinner(t_philosopher *phil, t_data *data);

//GENERAL UTILS FUNCTIONS

int     simple_atoi(char *nptr);
size_t  get_time_in_milliseconds (void);
void    ft_usleep(size_t milliseconds, t_data *data);
void    sem_locked_printing (size_t begin, sem_t *printing_semaphore, int philo_num, char *action);
void    ft_cleanup_and_exit(t_philosopher *phil, t_data *data, int exit_value);

#endif