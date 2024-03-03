#include "get_next_line.h"

// compilar:  cc -Wall -Werror -Wextra -g3 -D BUFFER_SIZE=42 get_next_line.c main.c libft.a
// el_quijote ---(2187)---- lineas aprox


int main(void)
{
	char *str;
	int i;
	int fd = open("txt.txt",O_RDONLY);
	//close(fd);
	//printf("%d", fd);
	i = 0;
	while(i < 26)
	{
		str = get_next_line(fd);
		if (!str)
		{
			printf("(nul)");
		}	
		else
		{
			printf("%s",str);
			free(str);
		}
		i++;
		printf("---(%d)----\n", i);
	}
	return(0);
}

/*notas
	linea vacia retorna NULL

*/
