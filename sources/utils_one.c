/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:34:45 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/21 15:45:22 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int simple_atoi(char *nptr)
{
    int atoi;
    int i;

    atoi = 0;
    i = 0;

    while (nptr != NULL && nptr[i] != 0)
    {
        atoi = atoi * 10 + (nptr[i] - 48);
        i++;
    }
    return (atoi);
}

bool    are_args_valid(int argc, char *argv[])
{
    int i;
    int x;

    i = 1;
    while (i < argc)
    {
        if(!argv)
            return (NULL);
        x = 0;
        while (argv[i][x] != 0)
        {
            if (argv[i][x] >= '0' && argv[i][x] <= '9')
                x++;
            else
                return (printf (MODE_BOLD ANSI_COLOR_RED "Insert only numbers as args!\n" ANSI_RESET), false);
        }
        i++;
    }
    return (true);
}

bool    are_arguments_in_limits(int argc, char *argv[])
{
    int i;
    int usleep_time;
    
    if (simple_atoi(argv[1]) > MAX_THREADS)
        return (printf (MODE_BOLD ANSI_COLOR_YELLOW MAX_PHILO_ERROR_MSG ANSI_RESET), false);
    i = 1;
    while (i < argc)
    {
        usleep_time = simple_atoi(argv[i]);
        if (usleep_time == 0)
            return (printf (MODE_BOLD ANSI_COLOR_YELLOW ZERO_ERROR ANSI_RESET), false);
        if (usleep_time > MAX_USLEEP)
            return (printf (MODE_BOLD ANSI_COLOR_YELLOW MAX_USLEEP_ERROR ANSI_RESET), false);
        i++;
    }
    return (true);
}

t_param_data *init_data_struct(int argc, char *argv[])
{
    t_param_data    *data;

    data = malloc(sizeof (t_param_data));
    if (data == NULL)
        return (printf("Memory allocation error\n"), NULL);
    data->is_phil_dead = false;
    data->philosophers_number = simple_atoi(argv[1]);
    data->die_time = simple_atoi(argv[2]);
    data->eat_time = simple_atoi(argv[3]);
    data->sleep_time = simple_atoi(argv[4]);
    if (argc == 6)
        data->how_many_spaghetti = simple_atoi(argv[5]);
    else    
        data->how_many_spaghetti = -1;
    if (pthread_mutex_init(&data->display_mutex, NULL) != 0)
        return (free(data), NULL);
    if (pthread_mutex_init(&data->update_mutex, NULL) != 0)
        return (pthread_mutex_destroy(&data->display_mutex), free(data), NULL);
    if (pthread_mutex_init(&data->bool_mutex, NULL) != 0)
        return (pthread_mutex_destroy(&data->update_mutex), pthread_mutex_destroy(&data->display_mutex), free(data), NULL);
    return (data);
}
