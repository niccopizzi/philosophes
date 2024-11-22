/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:23:47 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/22 09:16:52 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    read_or_update_death(t_param_data *data, char mode)
{
    bool            death_state;

    death_state = false;
    pthread_mutex_lock(&data->bool_mutex);
    if (mode == 'r')
        death_state = data->is_phil_dead;
    if (mode == 'u')
    {
        data->is_phil_dead = true;
        death_state = true;
    }
    pthread_mutex_unlock(&data->bool_mutex);
    return(death_state);
}

void    locked_printing(size_t begin, int phil_num, t_param_data *data, char *action)
{
    size_t      end;
    
    if (read_or_update_death(data, 'r') == true)
        return ;
    pthread_mutex_lock(&data->display_mutex);
    end = get_time_in_milliseconds();
    printf (MODE_BOLD "%ld %d %s\n", (end - begin) , phil_num, action);
    if (action[0] == 'd')
        read_or_update_death(data, 'u');
    pthread_mutex_unlock(&data->display_mutex);
}

size_t get_time_in_milliseconds (void)
{
    struct timeval now;

    if (gettimeofday(&now, NULL) == -1)
        printf ("There was an error in getting the time\n");
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
 
void    ft_usleep(size_t milliseconds, t_param_data *data)
{
    size_t  starting_milliseconds;
    
    starting_milliseconds = get_time_in_milliseconds();
    while (get_time_in_milliseconds() - starting_milliseconds < milliseconds && read_or_update_death(data, 'r') == false)
        usleep(100);
} 

