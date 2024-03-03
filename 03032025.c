/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03032025.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:25:37 by antofern          #+#    #+#             */
/*   Updated: 2024/03/03 20:31:31 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//copia buff hasta \n en line, asigna a buff "una nueva cadena con el resto". Si no hay \n setea la referencia de line a la direccion de buff, y pone buff a NULL.
// no deberia dejar en ningun caso una cadena vacia
void	pick_line(char **remind, char **line)
{
	char	*end_ln;
	char	*tmp;

	if (!*remind)
		return ;
	tmp = NULL;/////////////////////////////////////////
	end_ln = ft_strchr(*remind, '\n');
	if (!end_ln)
		*line = *remind;
	else
	{
		if (*(end_ln + 1) != '\0')////////////////////////////
		{//////////////////////////////////////////////////
			tmp = ft_strdup(end_ln + 1);
			if (!tmp)
				return ;
		}/////////////////////////////////////////////////
		*(end_ln + 1) = '\0';
		*line = ft_strdup(*remind);
		if (!*line)
			return ;
		free(*remind);
	}
	*remind = tmp;
}

int	get_read(int fd, char **buff)
{
	ssize_t	n;

	if (!*buff)
		*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buff)
		return (-1);
	n = read(fd, *buff, BUFFER_SIZE);
	if (n <= 0)
	{
		free(*buff);
		*buff = NULL;
		if (n == 0)
			return (1);
		return (-1);
	}
	(*buff)[n] = '\0';
	if (ft_strchr(*buff, '\n') || n < BUFFER_SIZE)
		return (1);
	return (0);
}

int	join_free(char **remind, char *buff, int read_stat)
{
	char	*tmp;

	if (!*remind)
	{
		*remind = buff;
		return (0);
	}
	tmp = ft_strjoin(*remind, buff);
	if (read_stat == 1 || !tmp)
		free(buff);
	if (!tmp)
		return (-1);
	free(*remind);
	*remind = tmp;
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*remind;
	char		*line;
	int			read_stat;

	if (fd < 0 || fd > 255)
		return (NULL);
	buff = NULL;
	line = NULL;
	if (remind && ft_strchr(remind, '\n'))
		pick_line(&remind, &line);
	else
	{
		read_stat = 0;
		while (read_stat == 0)
		{
			read_stat = get_read(fd, &buff);
			if (read_stat >= 0 && buff && join_free(&remind, buff, read_stat))
				read_stat = -1;
			if (read_stat == -1)
				return (NULL);
		}
		pick_line(&remind, &line);
	}
	return (line);
}
