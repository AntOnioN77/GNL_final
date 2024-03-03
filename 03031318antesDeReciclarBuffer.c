/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03031318antesDeReciclarBuffer.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antofern <antofern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:25:37 by antofern          #+#    #+#             */
/*   Updated: 2024/03/03 13:29:24 by antofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//copia buff hasta \n en line, asigna a buff "una nueva cadena con el resto". Si no hay \n setea la referencia de line a la direccion de buff, y pone buff a NULL.
// no deberia dejar en ningun caso una cadena vacia
pick_line(char **line, char **buff)
{
	if (!buff)
		return (0);
}

int	get_read(int fd, char **buff)
{
	ssize_t	n;

	if (*buff)
		free(*buff);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	buff[BUFFER_SIZE] = '\0';
	n = read(fd, buff, BUFFER_SIZE);
	if (n <= 0)
	{
		free(buff);
		buff = NULL;
		if (n == 0)
			return (1);
		return (-1);
	}
	if (ft_strchr(*buff, '\n') || n < BUFFER_SIZE)
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*remind;
	char		*line;
	int			read_stat;

	buff = NULL;
	if (remind && ft_strchr(remind))
		pick_line(&remind, &line);
	else
	{
		read_stat = 0;
		while (read_stat == 0)
		{
			read_stat = get_read(fd, &buff);
			if (read_stat >= 0 && buff) //buff se queda porque en caso de que get_read haga una lectura de 0 read_state=1 y buffer=NULL. No necesitamos unir cero a nada
				if (join_free(&remind, buff))
					read_stat = -1;
			if (read_stat == -1)
				return (NULL);
		}
		pick_line(&remind, &line);
	}
	return (line);
}

int	join_free(char **remind, char *buff)
{
	char	*tmp;
	
	if (!*remind)
	{
		*remind = buff;
		return (0);
	}
	tmp = ft_strjoin(*remind, buff);
	free(buff);
	if (!tmp)
		return (-1);
	free(*remind);
	*remind = tmp;
	return (0);
}
