#include "pipex_bonus.h"

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
void	ft_wait(int pid, int st, t_dat *in, t_desc *des)
{
	int	res;

	res = waitpid(pid, &st, WNOHANG);//guardo resultado del waitpid
	if (res == -1)
	{
		perror ("Waitpid error");
		ft_free_des (in, des);
	}
	if (WIFEXITED(st) == 0)
	{
		perror ("Child end error");
		ft_free_des (in, des);
	}
}

//fork function with errors control
void	ft_fork(t_dat *in, t_desc *des, int i)
{
	des->pidfd[i] = fork();
	if (des->pidfd[i] == -1)
	{
		perror ("Fork error");
		ft_free_des (in, des);
	}
}

//dup2 function with errors control
void	ft_dup2(int desold, int desnew, t_dat *in, t_desc *des)
{
	int	i;

	i = dup2 (desold, desnew);
	if (i == -1)
	{
		perror ("Dup2 error");
		ft_free_des (in, des);
	}
}
