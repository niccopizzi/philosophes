/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:31:39 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/25 17:55:15 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t get_time_in_milliseconds (void)
{
    struct timeval now;

    if (gettimeofday(&now, NULL) == -1)
        printf ("There was an error in getting the time\n");
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
 
void    ft_usleep(size_t milliseconds, t_data *data)
{
    size_t  starting_milliseconds;

    (void)data;
    
    starting_milliseconds = get_time_in_milliseconds();
    while (get_time_in_milliseconds() - starting_milliseconds < milliseconds)
        usleep(100);
} 

void    sem_locked_printing (size_t begin, sem_t *printing_semaphore, int philo_num, char *action)
{
    size_t      end;

    end = get_time_in_milliseconds();
    
    sem_wait (printing_semaphore);
    printf ("%ld %d %s\n", end - begin, philo_num, action);
    fflush(stdout);
    sem_post(printing_semaphore);
}