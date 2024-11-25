/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:54:59 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/25 18:05:55 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data  *ft_init_data_struct(int argc, char *argv[])
{
    t_data  *data;

    data = malloc(sizeof(t_data));
    if (data == NULL)
        return (printf ("Malloc error\n"), NULL);
    data->philosophers_number = simple_atoi(argv[1]);
    data->die_time = simple_atoi(argv[2]);
    data->eat_time = simple_atoi(argv[3]);
    data->sleep_time = simple_atoi(argv[4]);
    if (argc == 6)
        data->how_many_spaghetti = simple_atoi(argv[5]);
    else    
        data->how_many_spaghetti = -1;
    data->printing_semaphore = sem_open (PRINT_SEM_NAME, O_CREAT, 0666, 1);
    if (data->printing_semaphore == SEM_FAILED)
        return (free(data), printf ("Error in opening the semaphore\n"), NULL);
    data->fork_semaphore = sem_open (FORK_SEM_NAME, O_CREAT, 0666, data->philosophers_number);
    if (data->fork_semaphore == SEM_FAILED)
        return (sem_close (data->printing_semaphore), sem_unlink (PRINT_SEM_NAME),
                free(data), printf ("Error in opening the semaphore\n"),  NULL);
    return (data);
}

t_philosopher *ft_init_philo_struct(t_data *data)
{
    t_philosopher *phil;

    phil = malloc(sizeof(t_philosopher));
    if (phil == NULL)
    {
        printf ("Error in malloc\n");
        sem_close(data->printing_semaphore);
        sem_close(data->fork_semaphore);
        free(data);
        sem_unlink(FORK_SEM_NAME);
        sem_unlink(PRINT_SEM_NAME);
        return(NULL);
    }
    phil->data = data;
    return (phil);
}