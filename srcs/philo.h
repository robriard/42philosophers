/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:39:17 by robriard          #+#    #+#             */
/*   Updated: 2021/08/16 13:13:39 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# ifndef RETURNS
#  define RETURN_SUCCESS 0
#  define RETURN_FAILURE 1
# endif

typedef suseconds_t		t_ms;
typedef pthread_mutex_t	t_mutex;

typedef struct s_args
{
	t_ms		die;
	t_ms		eat;
	t_ms		sleep;
	long int	max_laps;
}				t_args;

typedef struct s_philo
{
	int			id;
	t_ms		die;
	t_ms		eat;
	t_ms		sleep;
	long int	max_laps;
	t_mutex		*lfork;
	t_mutex		*rfork;
	t_mutex		*printer;
}				t_philo;

/*
 *		TOOLS
 */
t_ms	ft_atoi(const char *s);
void	clean_philo(t_philo **philos, int index);
void	exit_(int status);
int		is_num(const char *s);

/*
 *		PHILO
 */
void	thread_manager(int pop, t_args args);

#endif
