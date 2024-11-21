/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:38:02 by npizzi            #+#    #+#             */
/*   Updated: 2024/11/21 16:10:10 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
    t_param_data *data;
    t_philosopher *head;
    
    if (argc < 5 || argc > 6)
        return (printf (MODE_BOLD ANSI_COLOR_RED INVALID_PARAM_NUM_MSG ANSI_RESET) , 1);
    if (are_args_valid(argc, argv) == false || are_arguments_in_limits(argc, argv) == false)
        return (2);
    data = init_data_struct(argc, argv);
    if (data == NULL)
        return (4);
    head = init_philo(data);
    if (head == NULL)
        return (5);
    start_the_dinner(head, data, data->philosophers_number);
    ft_free_all(&head, &data);
    return (0);
}
