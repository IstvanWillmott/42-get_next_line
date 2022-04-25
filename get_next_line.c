/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:42:35 by iwillmot          #+#    #+#             */
/*   Updated: 2022/04/25 13:08:11 by iwillmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_foundn(char *save)
{
	int	i;

	i = 0;
	if (!save)
		return (0);
	while (save[i])
	{
		if (save[i] == '\n')
			return (++i);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *save, char *buff)
{
	char	*new;
	int		i;
	int		x;

	i = 0;
	x = 0;
	new = malloc(ft_strlen(save) + ft_strlen(buff) + 1);
	if (save)
		while (save[x])
			new[i++] = save[x++];
	x = 0;
	if (buff)
		while (buff[x])
			new[i++] = buff[x++];
	new[i] = '\0';
	if (save)
		free(save);
	return (new);
}

char	*ft_assignline(char **save)
{
	int		i;
	int		x;
	char	*line;
	char	*store;

	i = ft_foundn(*save);
	if (i == 0)
		i = ft_strlen(*save);
	line = malloc(i + 1);
	line[i] = '\0';
	while (i-- > 0)
		line[i] = (*save)[i];
	store = NULL;
	i = ft_strlen(*save) - ft_foundn(*save);
	if (i != ft_strlen(*save) && i > 0)
	{
		store = malloc(i + 1);
		store[i++] = '\0';
		x = ft_strlen(*save);
		while (i-- > 0)
			store[i] = (*save)[x--];
	}
	free(*save);
	*save = store;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save[500];
	int			n;
	char		*buff;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	while (!ft_foundn(&save[fd][0]))
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == 0)
			break ;
		buff[n] = '\0';
		save[fd] = ft_strjoin(save[fd], buff);
	}
	free(buff);
	if (save[fd])
		return (ft_assignline(&save[fd]));
	return (NULL);
}
