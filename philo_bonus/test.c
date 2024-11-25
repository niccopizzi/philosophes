#include "philo_bonus.h"

void start_the_phil(t_data *sems)
{
    int x;
    int id;

    x = 1;
    while (x <= 10)
    {
        id = fork();
        if (id == CHILD_PROCESS)
            break;
        x++;
    }
    if (id == CHILD_PROCESS)
    {
        if (x == 7)
        {
            usleep (5000);
            sems->is_phil_dead = true;
        }
        sem_wait (sems->fork_semaphore);
        sem_locked_printing (sems->printing_semaphore, "took a fork");
        sem_wait (sems->fork_semaphore);
        sem_locked_printing (sems->printing_semaphore, "took a fork");
        sem_post (sems->fork_semaphore);
        sem_post (sems->fork_semaphore);
        if(sems->is_phil_dead == true)
            sem_locked_printing (sems->printing_semaphore, "die a fork");
        sem_close (sems->printing_semaphore);
        sem_close (sems->fork_semaphore);
        free (sems);
        exit (EXIT_SUCCESS);
    }
    else
    {
        while (x -- > 0)
            waitpid (-1, NULL, 0);
    }
}

int main(void)
{
    t_data    *sems;
    
    sems = malloc(sizeof(t_data));
    if (sems == NULL)
        return (2);
    sem_unlink (PRINT_SEM_NAME);
    sem_unlink (FORK_SEM_NAME);
    
    sems->printing_semaphore = sem_open (PRINT_SEM_NAME, O_CREAT, 0666, 1);
    if (sems->printing_semaphore == SEM_FAILED)
        return (perror ("Error in opening the sempahore\n"), 1);
    sems->fork_semaphore = sem_open (FORK_SEM_NAME, O_CREAT, 0666, 10);
    if (sems->fork_semaphore == SEM_FAILED)
        return (perror ("Error in opening the semaphore\n"), 1);
    start_the_phil(sems);
    sem_close (sems->printing_semaphore);
    sem_close (sems->fork_semaphore);
    sem_unlink (PRINT_SEM_NAME);
    sem_unlink (FORK_SEM_NAME);
    free (sems);
    return (0);
}