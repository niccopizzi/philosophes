/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:13:47 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/21 16:07:05 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

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
#define MAX_USLEEP_ERROR "Woah, that's a big number! Usleep doesn't like it :("

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_param_data
{
    bool                    is_phil_dead;
    int                     how_many_spaghetti;
    int                     philosophers_number;
    __useconds_t            die_time;
    __useconds_t            eat_time;
    __useconds_t            sleep_time;
    size_t                  starting_milliseconds;
    pthread_mutex_t         display_mutex;
    pthread_mutex_t         update_mutex;
    pthread_mutex_t         bool_mutex;
    
}   t_param_data;

typedef struct s_philosopher
{
    int                     philosopher_num;
    int                     spaghetti_eaten;
    size_t                  last_meal;
    pthread_t               thread;
    pthread_mutex_t         fork_mutex;
    struct s_param_data     *data;
    struct s_philosopher    *previous;
    struct s_philosopher    *next;

}   t_philosopher;


//CHECKER FUNCTIONS 

bool            are_args_valid(int argc, char *argv[]);
bool            are_arguments_in_limits(int argc, char *argv[]);

//STRUCT INITIALIZING FUNCTIONS

t_philosopher   *init_philo(t_param_data *data);
t_param_data    *init_data_struct(int argc, char *argv[]);

//THREADS FUNCTIONS


int             start_the_dinner_for_one(t_philosopher *head, t_param_data *data);
int             start_the_dinner(t_philosopher *head, t_param_data *data, int phil_num);
void            *dinner_for_one(void *phil_head);
void            *dinner(void *philosopher_head);

//GENERAL UTILS FUNCTIONS

bool                read_or_update_death(t_param_data *data, char mode);
void                ft_usleep(size_t milliseconds, t_param_data *data);
void                ft_free_all(t_philosopher **head, t_param_data **data);
void                locked_printing(size_t begin, int phil_num, t_param_data *data, char *action);
int                 simple_atoi(char *nptr);
size_t              get_time_in_milliseconds (void);

#endif
