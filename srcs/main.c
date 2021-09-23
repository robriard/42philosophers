/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:37:19 by robriard          #+#    #+#             */
/*   Updated: 2021/09/21 14:18:09 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_(int status)
{
	if (status != 0)
		printf("Error\n");
	exit(status);
}

static int	parser(int ac, char **args, t_args *struc)
{
	int		i;
	time_t	buf[4];

	i = 0;
	while (i < 4)
	{
		buf[i] = -1;
		i++;
	}
	i = 1;
	while (args[i])
	{
		if (is_num(args[i]))
			return (RETURN_ERROR);
		buf[i - 1] = ft_atoi(args[i]);
		if (buf[i - 1] <= 0)
			return (RETURN_ERROR);
		i++;
	}
	if (ac == 6 && buf[3] <= 0)
		return (RETURN_ERROR);
	struc->die = buf[0] * 1000;
	struc->eat = buf[1] * 1000;
	struc->sleep = buf[2] * 1000;
	struc->max_laps = (long int)buf[3];
	return ((int)ft_atoi(args[0]));
}

int	main(int ac, char **av)
{
	t_args		args;
	int			pop;

	g_time = 0;
	g_time = get_time();
	if (ac != 5 && ac != 6)
		exit_(EXIT_FAILURE);
	pop = parser(ac, av + 1, &args);
	if (pop <= 0)
		exit_(EXIT_FAILURE);
	thread_manager(pop, args);
	return (0);
}
