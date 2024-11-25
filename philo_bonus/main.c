/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:29:51 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/25 18:13:28 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int argc, char *argv[])
{
    t_data          *data;
    t_philosopher   *phil;
    
    if (argc < 5 || argc > 6)
        return (printf (MODE_BOLD ANSI_COLOR_RED INVALID_PARAM_NUM_MSG ANSI_RESET) , 1);
    if (are_args_valid(argc, argv) == false || are_arguments_in_limits(argc, argv) == false)
        return (2);
    sem_unlink(FORK_SEM_NAME);
    sem_unlink(PRINT_SEM_NAME);
    data = ft_init_data_struct(argc, argv);
    if (data == NULL)
        return (3);
    phil = ft_init_philo_struct(data);
    if (phil == NULL)
        return (4);
    start_the_dinner(phil, data);
    ft_cleanup_and_exit(phil, data, 2);
    sem_unlink(FORK_SEM_NAME);
    sem_unlink(PRINT_SEM_NAME);
    return (0);
}