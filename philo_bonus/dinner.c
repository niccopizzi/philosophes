/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:35:55 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/25 18:16:21 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* void    checking_routine(void *phil)
{
    
} */

void    sleep_routine(sem_t *printing_semaphore, t_data *data, t_philosopher *phil)
{
    int phil_num;

    phil_num = phil->philosopher_num;
    sem_locked_printing(data->starting_milliseconds, printing_semaphore, phil_num, "is sleeping");
    ft_usleep(data->sleep_time, data);
    sem_locked_printing(data->starting_milliseconds, printing_semaphore, phil_num, "is thinking");
    ft_usleep(1, data);
    
}

void    take_forks(sem_t *fork_semaphore, sem_t *printing_semaphore, t_data *data, int phil_num)
{
    if (phil_num % 2 != 0)
        ft_usleep(10, data);
    sem_wait(fork_semaphore);
    sem_locked_printing(data->starting_milliseconds, printing_semaphore, phil_num, "has taken a fork");
    sem_wait(fork_semaphore);
    sem_locked_printing(data->starting_milliseconds, printing_semaphore, phil_num, "has taken a fork");
}

void    dinner_routine(sem_t *fork_semaphore, sem_t *printing_semaphore, t_data *data, t_philosopher *phil)
{
    int phil_num;

    phil_num = phil->philosopher_num;
    take_forks(fork_semaphore, printing_semaphore, data, phil_num);
    phil->last_meal = get_time_in_milliseconds();
    sem_locked_printing(data->starting_milliseconds, printing_semaphore, phil_num, "is eating");
    ft_usleep(data->eat_time, data);
    sem_post(fork_semaphore);
    sem_post(fork_semaphore);
    phil->spaghetti_eaten += 1;
    sleep_routine(printing_semaphore, data, phil);
    return;
}

void    start_the_dinner(t_philosopher *phil, t_data *data)
{
    int     i;
    int     id;
    pid_t   childrens_pids[data->philosophers_number];

    
    i = 0;
    id = 1;
    data->starting_milliseconds = get_time_in_milliseconds();
    while (i < data->philosophers_number)
    {
        if (id = fork(), id == CHILD_PROCESS)
            break;
        childrens_pids[i] = id;
        i++;
    }
    if (id == CHILD_PROCESS)
    {
        phil->philosopher_num = i + 1;
        dinner_routine(data->fork_semaphore, data->printing_semaphore, data, phil);
        ft_cleanup_and_exit(phil, data, EXIT_SUCCESS);
    }   
    else
    {
        while (--i >= 0)
        {
            fflush(stdout);
            waitpid (childrens_pids[i], NULL, 0);
        }     
    }
}


/*t_philosopher  *get_last_meal(t_philosopher *phil_head)
{
    t_philosopher   *ptr;
    t_philosopher   *phil;
    int             i;
    
        
    ptr = phil_head;
    phil = ptr;
    i = phil ->data ->philosophers_number;
    while (i -- > 0)
    {
        if (ptr ->last_meal < phil ->last_meal)
            phil = ptr;  
        ptr = ptr ->next;
    }
    return (phil);
}

void    *death_check_routine(void *phil_head)
{
    t_philosopher   *ptr;
    t_philosopher   *phil;
    size_t          die_time;
    size_t          current_time;
    
    ptr = (t_philosopher *)phil_head;
    die_time = ptr ->data ->die_time;
    while(true)
    {
        pthread_mutex_lock(&ptr->data->update_mutex);
        phil = get_last_meal(ptr);
        if (phil ->spaghetti_eaten == phil ->data ->how_many_spaghetti)
            return (pthread_mutex_unlock(&ptr->data->update_mutex), NULL);
        current_time = get_time_in_milliseconds();
        if (current_time - phil->last_meal >= die_time)
        {
            locked_printing (phil->data->starting_milliseconds, phil->philosopher_num, phil->data, "died");
            return ( pthread_mutex_unlock(&ptr->data->update_mutex), NULL);
        }
        pthread_mutex_unlock(&ptr->data->update_mutex);
        usleep(200);
    }
    return (NULL);
}*/