//escribir en get_next_line.h:
extern int next_read_error;//////////////////borraesto
# define MALLOC_FAIL 0////////////borraesto

//forzar error de lectura. 0 no genera error, 1 si
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
}

// n es una cuenta atras, el n`esimo malloc fallará. 0 No falla
void 	*ft_malloc(size_t n)
{
	static int fail_at = MALLOC_FAIL;

	if (fail_at == 1)
	{
		fail_at = 0;
		return  (NULL);
	}
	else
	{
		fail_at--;
		return(malloc(n));
	}
}