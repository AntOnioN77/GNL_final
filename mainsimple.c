#include "get_next_line.h"

int main(void)
{
	char *str;
	int i;
	int fd = open("variosnl.txt",O_RDONLY);
	//close(fd);
	//printf("%d", fd);
	i = 0;
	while(i < 7)
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
	return (0);
}
