/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robriard <robriard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:25:26 by robriard          #+#    #+#             */
/*   Updated: 2021/10/16 10:09:46 by robriard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

time_t	ft_atoi(const char *s)
{
	int		signe;
	time_t	result;

	result = 0;
	signe = 1;
	while (*s == '\t' || *s == '\n' || *s == '\v' || *s == '\r'
		|| *s == '\f' || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			signe = -1;
		s++;
	}
	if (*s == '\t' || *s == '\n' || *s == '\v' || *s == '\r'
		|| *s == '\f' || *s == ' ' || *s == '+' || *s == '-')
		return (0);
	while (*s >= 48 && *s <= 57)
	{
		result = result * 10 + (*s - 48);
		s++;
	}
	return (result * signe);
}

int	is_num(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		i;
	int		j;

	dst = malloc(sizeof(char) * (1 + ft_strlen(s1) + ft_strlen(s2)));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

void	print(t_philo *philo, char *msg, time_t now)
{
	pthread_mutex_lock(&philo->env->printer);
	if (!statecmp(philo, Alive))
		printf(msg, now, philo->id);
	pthread_mutex_unlock(&philo->env->printer);
}
