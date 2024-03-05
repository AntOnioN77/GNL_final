
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h> //borra esto y cambia en el archivo .c las llamadas por ft_*

extern int next_read_error;//////////////////borraesto

char	*get_next_line(int fd);
int		get_read(int fd, char **buff, char *remind);
int		join_free(char **remind, char **buff, int read_stat);
int		pick_line(char **remind, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);

#endif