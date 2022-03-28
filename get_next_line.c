/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwillmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:44:51 by iwillmot          #+#    #+#             */
/*   Updated: 2022/03/28 18:12:12 by iwillmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*returnchar(char *save, char *final)
{
	char	*new;
	int		i;

	i = 0;
	while ((save[i] != '\n') && (save[i] != '\0'))
		i++;
	new = malloc(i);
	i = 0;
	while ((save[i] != '\n') && (save[i] != '\0'))
	{
		new[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

int	search_n(char *buff)
{
	int ret;
	int	i;

	ret = 0;
	i = 0;
	while ((buff[i]) && (ret == 0))
	{
		if (buff[i] == '\n')
			ret = 1;
		i++;
	}
	return (ret);
}
char	*strjoin(char *dest, char *cpy)
{
	char	*new;
	int		dlen;
	int 	clen;

	dlen = 0;
	clen = 0;
	while (dest[dlen])
		dlen++;
	while (cpy[clen])
		clen++;
	new = malloc(dlen + clen + 1);
	dlen = 0;
	clen = 0;
	while (dest[dlen])
	{
		new[dlen] = dest[dlen];
		dlen++;
	}
	while (cpy[clen])
	{
		new[dlen + clen] = cpy[clen];
		clen++;
	}
	new[dlen + clen] = '\0';
	free(dest);
	return (new);
}

char	*readsave(int fd, char *save)
{
	char	*buff;
	int		last;
	int		read_len;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	read_len = 1;
	last = 0;
	while ((last == 0) && (read_len != 0))
	{
		read_len = read(fd, buff, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_len] = '\0';
		last = search_n(buff);
		save = strjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	//char		*line;
	static char	*save;
	static char	*final;

	save = (char *)malloc(1);
	save[0] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = readsave(fd, save);
	if (save)
		free(save);
	return (returnchar(save, final));
}
