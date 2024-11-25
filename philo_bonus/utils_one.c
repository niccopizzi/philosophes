/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:14:35 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/25 18:05:34 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


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

void    ft_cleanup_and_exit(t_philosopher *phil, t_data *data, int exit_value)
{
    free(phil);
    sem_close(data->fork_semaphore);
    sem_close(data->printing_semaphore);
    free(data);
    if (exit_value == 0 || exit_value == 1)
        exit(exit_value);
}