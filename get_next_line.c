/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:25:37 by antofern          #+#    #+#             */
/*   Updated: 2024/03/06 14:52:39 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//!!!!!!!!!!!!!!!!!!! si hay un error de lectura hay que cargarse remind (hacerle free, NULL)
/*
int next_read_error = 0;
ssize_t ft_bad_read(int fd, void *buf, size_t count)
{
	if(!next_read_error)
		return (read(fd, buf, count));
	else
	{
		printf("[[[mala lectura]]]");
		return (-1);
	}
}*/

//copia buff hasta \n en line, asigna a buff "una nueva cadena con el resto". Si no hay \n setea la referencia de line a la direccion de buff, y pone buff a NULL.
// no deberia dejar en ningun caso una cadena vacia
void	free_null(void **pnt)
{
	if (*pnt)
	{
		free(*pnt);
		*pnt = NULL;
	}
}

int	pick_line(char **remind, char **line)
{
	char	*end_ln;
	char	*tmp;

	tmp = NULL;
	end_ln = ft_strchr(*remind, '\n');
	if (!end_ln)
		*line = *remind;
	else
	{
		if (*(end_ln + 1) != '\0')
		{
			tmp = ft_strdup(end_ln + 1);
			if (!tmp)
			{
				*line = NULL;
				return (-1);
			}
		}
		*(end_ln + 1) = '\0';
		*line = ft_strdup(*remind);
		free_null((void **)remind);
		if (!*line)
		{
			free(tmp);
			return (-1);
		}
	}
	*remind = tmp;
	return (2);
}

int	get_read(int fd, char **buff, char *remind)
{
	ssize_t	n;

	if (!*buff || *buff == remind)
		*buff = (char *)ft_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!*buff)
		return (-1);
	n = read(fd, *buff, BUFFER_SIZE); ///////////////////////ft_bad_read
	if (n <= 0)
	{
		free_null((void **)buff);
		if (n == 0)
			return (1);
		return (-1);
	}
	(*buff)[n] = '\0';
	if (ft_strchr(*buff, '\n') || n < BUFFER_SIZE)
		return (1);
	return (0);
}

int	join_it(char **remind, char **buff, int stat)
{
	char	*tmp;

	if (!*remind)
	{
		*remind = ft_strdup(*buff);
		free_null((void **)buff);
		return (0);
	}
	tmp = ft_strjoin(*remind, *buff);
	if (stat == 1 || !tmp)
		free(*buff);
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
	int			stat;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = NULL;
	line = NULL;
	stat = 0;
	while (stat == 0)
	{
		if (remind && ft_strchr(remind, '\n'))
			stat = pick_line(&remind, &line);
		if (stat == 0)
			stat = get_read(fd, &buff, remind);
		if ((stat == 0 || stat == 1) && buff && join_it(&remind, &buff, stat))
			stat = -1;
	}
	if ((stat == 1) && remind)
		stat = pick_line(&remind, &line);
	if (stat == -1)
		free_null((void **)&remind);
	return (line);
}
