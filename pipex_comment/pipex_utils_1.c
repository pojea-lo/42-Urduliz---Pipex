#include "pipex.h"

//close function with errors control
void	ft_close(int descr)
{
	int	i;

	i = 0;
	if (descr != 0 && descr != 1 && descr != 2)
		i = close (descr);
	if (i == -1)
		perror ("Close error");
}

//waitpid function with errors control
void	ft_wait(int pid, int st, t_dat *in)
{
	int	res;

//	res = waitpid(pid, &st, WNOHANG);//guardo resultado del waitpid
	res = waitpid(pid, &st, 0);//guardo resultado del waitpid
	if (res == -1)
	{
		perror ("Waitpid error");
		ft_free (in);
	}
/*	if (WIFEXITED(st) == 0)
	{
		perror ("Child end error");
		ft_free (in);
	}*/
}

//dup2 function with errors control
void	ft_dup2(int desold, int desnew, t_dat *in)
{
	int	i;

	i = dup2 (desold, desnew);
	if (i == -1)
	{
		perror ("Dup2 error");
		ft_free (in);
	}
}
