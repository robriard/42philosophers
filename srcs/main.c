/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:37:19 by robriard          #+#    #+#             */
/*   Updated: 2021/08/16 13:13:55 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_(int status)
{
	if (status != 0)
		printf("Error\n");
	exit(status);
}

static int	parser(char **args, t_args *struc)
{
	int			i;
	t_ms		buf[4];

	i = 0;
	while (i < 4)
	{
		buf[i] = -1;
		printf("%d\n", buf[i]);
		i++;
	}
	i = 1;
	while (args[i])
	{
		if (is_num(args[i]))
			return (-1);
		buf[i - 1] = ft_atoi(args[i]);
		if (buf[i - 1] <= 0)
			return (-1);
		i++;
	}
	struc->die = buf[0];
	struc->eat = buf[1];
	struc->sleep = buf[2];
	printf("{%d}\n", buf[3]);
	struc->max_laps = buf[3];
	printf("{%li}\n", struc->max_laps);
	return ((int)ft_atoi(args[0]));
}

int	main(int ac, char **av)
{
	t_args		args;
	int			pop;

	if (ac != 5 && ac != 6)
		exit_(EXIT_FAILURE);
	pop = parser(av + 1, &args);
	if (pop <= 0)
		exit_(EXIT_FAILURE);
	thread_manager(pop, args);
	return (0);
}
