/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 18:19:42 by rcollas           #+#    #+#             */
/*   Updated: 2021/06/03 14:25:13 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_end_of_line(char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		if (str[i++] == '\n')
			return (i);
	return (0);
}

void	ft_after_newline(char *str, unsigned int start)
{
	char			*tmp;
	unsigned int	i;

	if (!str)
		return ;
	tmp = str;
	i = 0;
	while (tmp[start])
		str[i++] = tmp[start++];
	str[i] = 0;
}

int	get_next_line(int fd, char **line)
{
	char static	buff[BUFFER_SIZE + 1];
	int			is_reading;

	if (read(fd, buff, 0) == -1 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	is_reading = 1;
	*line = ft_strdup("");
	*line = ft_strjoin(*line, buff);
	while (is_reading > 0 && !ft_end_of_line(*line))
	{
		is_reading = read(fd, buff, BUFFER_SIZE);
		buff[is_reading] = 0;
		if (is_reading == 0)
			break ;
		if (is_reading == -1)
			return (-1);
		*line = ft_strjoin(*line, buff);
	}
	if (ft_end_of_line(*line))
		*line = ft_substr(*line, 0);
	ft_after_newline(buff, ft_end_of_line(buff));
	if (is_reading == 0)
		return (ft_bzero(buff));
	return (1);
}
