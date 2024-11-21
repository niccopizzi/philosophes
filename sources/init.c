/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:29:11 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/21 16:18:01 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_free_all(t_philosopher **head, t_param_data **data)
{
    int philo_num;
    t_philosopher *node;
    
    while(*head != NULL)
    {
        node = (*head)->next;
        philo_num = (*head)->philosopher_num;
        pthread_mutex_destroy (&(*head)->fork_mutex);
        free (*head);
        *head = NULL;
        (*head) = node;
        if (philo_num == (*data) ->philosophers_number)
            break;        
    }
    pthread_mutex_destroy(&(*data)->display_mutex);
    pthread_mutex_destroy(&(*data)->update_mutex);
    pthread_mutex_destroy(&(*data)->bool_mutex);
    free(*data);
    *data = NULL;
}

t_philosopher *ft_init_philo_node(int n, t_param_data *data)
{
    t_philosopher *node;
    
    node = malloc(sizeof(t_philosopher));
    if(node == NULL)
        return (printf ("ERROR IN ALLOCATING MEMORY FOR THE NODE\n"), NULL);
    node->philosopher_num = n;
    if (pthread_mutex_init(&node->fork_mutex, NULL) != 0)
    {
        printf (MODE_BOLD ANSI_COLOR_RED "Error in initializing the mutex\n" ANSI_RESET);
        free (node);
        return (NULL);
    }
    node->spaghetti_eaten = 0;
    node->data = data;
    node->next = NULL;
    node->previous = NULL;
    return (node);
}

t_philosopher  *init_philo(t_param_data *data)
{
    t_philosopher   *head;
    t_philosopher   *node;
    int i;
    
    head = ft_init_philo_node(1, data);
    if(head == NULL)
        return (NULL);
    i = 1;
    node = head;
    while (++i <= data->philosophers_number)
    {
        node->next = ft_init_philo_node(i, data);
        if (node->next == NULL)
            return (ft_free_all(&head, &data), NULL);
        node->next->previous = node;
        node = node->next;
    }
    if (node != head)
    {
        node->next = head;
        head->previous = node;
    }
    return (head);
}

