/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:13:46 by eburnet           #+#    #+#             */
/*   Updated: 2024/11/07 11:36:07 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philos.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_isdigit(char n)
{
	if (n >= '0' && n <= '9')
		return (1);
	return (0);	
}

int	ft_atoi(char *str)
{
	int		i;
	int		isnegative;
	int		result;

	i = 0;
	isnegative = 1;
	result = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_isdigit(str[i]) && str[i] != '\0' && str[i] != '+')
		return (-1);
	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] != '\0' && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-' )
			isnegative *= -1;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - 48);
	return (result * isnegative);
}
