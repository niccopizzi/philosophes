/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:54:59 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/22 16:26:27 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *run_routine(void *arg)
{
    sem_t   *routine_sem;
    
    routine_sem = (sem_t *)arg;
    sem_wait(routine_sem);
    printf("Ello\n");
    sleep(1);
    sem_post(routine_sem);
    return (NULL);
}

int main()
{
    pthread_t t_arr[20];
    sem_t *sem;
    
    sem_unlink(SEM_NAME);
    sem = sem_open(SEM_NAME, O_CREAT, 0660, 0);
    if (sem == SEM_FAILED)
    {
        perror("SEM FAILED :" );
        return(1);
    }
    for (int i = 0; i < 20; i++)
    {
        if(pthread_create(&t_arr[i], NULL, run_routine, (void *)sem) != 0)
            perror("Error in creating the thread\n");
    }

    for (int i = 0; i < 20; i++)
    {
        if(pthread_join(t_arr[i], NULL) != 0)
            perror("Error in joining the thread\n");
    }

    sem_close(sem);
    sem_unlink(SEM_NAME);
    return (0);
}
