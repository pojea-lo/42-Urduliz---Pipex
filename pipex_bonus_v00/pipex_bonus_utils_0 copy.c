#include "pipex_bonus.h"

void	ft_open(t_dat *in)
{
	t_desc	des;
	int		i;

	des.fds = open ("int_file", O_RDONLY);
	des.fde = open ("ext_file", O_WRONLY);
	if (des.fds == -1 || des.fde == -1)
	{
		write (1, "Open error\n", 11);
//		ft_free(in);
	}
	des.fd = (int **) malloc (sizeof(int *) * (in->ncmd - 1));
//	if (in.fd == NULL)
//		ft_free (in);
	i = -1;
	while (++i < (in->ncmd - 1))
	{
		des.fd[i] = (int *) malloc (sizeof(int) * 2);
//		if (in.fd[i] == NULL)
//			ft_free (in);
	}
	des.pidfd = (int *) malloc (sizeof (int) * (in->ncmd - 1));
	des.stfd = (int *) malloc (sizeof (int) * (in->ncmd - 1));
//	if (in.pidfd == NULL || in.stfd == NULL)
//		ft_free (in);
	if (pipe(&des.pidfd[0]) == -1)
	{
		write (1, "Pipe error\n", 11);
//		ft_free (in);
	}
	ft_fork_start (in, &des);
}

//initial fork taking fds like inpunt
void	ft_fork_start(t_dat *in, t_desc *des)
{
	des->pidfd[0] = fork();
	if (des->pidfd[0] == 0)
	{
		close (des->fd[0][0]);
		dup2 (des->fd[0][1], STDOUT_FILENO);
		dup2 (des->fds, STDIN_FILENO);
		close (des->fd[0][1]);
		close (des->fds);
		printf ("la ruta: %s\n", in->fcmd[0][in->c[0]]);
		printf ("el comando inicial: %s\n", in->cmd[0][0]); 
		execve (in->fcmd[0][in->c[0]], in->cmd[0], in->env);
		exit(0);
	}
	else
	{
		close (des->fd[0][1]);
		ft_fork_final (in, des);
	}
	waitpid(des->pidfd[0], &des->stfd[0], 0);
	waitpid(des->pidfd[in->ncmd - 2], &des->stfd[in->ncmd - 2], 0);
//	ft_free (in);
}

//final fork taking fde like exit
void	ft_fork_final(t_dat *in, t_desc *des)
{
	printf ("ncmd: %d\n", in->ncmd);
	des->pidfd[in->ncmd - 2] = fork();
	if (des->pidfd[in->ncmd - 2] == 0)
	{
		dup2 (des->fd[in->ncmd - 2][0], STDIN_FILENO);
		close (des->fd[in->ncmd - 2][0]);
		dup2 (des->fde, STDOUT_FILENO);
		close (des->fde);
		printf ("el fcmd: %s, el cmd: %s\n", in->fcmd[in->ncmd - 1][in->c[in->ncmd - 1]], in->cmd[in->ncmd - 1][0]);
		execve (in->fcmd[in->ncmd - 1][in->c[in->ncmd - 1]], in->cmd[in->ncmd - 1], in->env);
		exit(0);
	}
	else
		close (des->fd[in->ncmd - 2][0]);
}
/*
void	ft_free(t_dat *in)
{
	int	i;

	if (in->fs != NULL)
		free (in->fs);
	if (in->fe != NULL)
		free (in->fe);
	if (in->cmd1 != NULL)
	{
		i = -1;
		while (in->cmd1[++i] != NULL)
			free (in->cmd1[i]);
		free (in->cmd1);
		i = -1;
		while (in->cmd2[++i] != NULL)
			free (in->cmd2[i]);
		free (in->cmd2);
	}
	if (in->env != NULL)
	{
		i = -1;
		while (in->env[++i] != NULL)
			free (in->env[i]);
		free (in->env);
	}
	ft_free_end(in);
}

void	ft_free_end(t_dat *in)
{
	int	i;

	if (in->fcmd1 != NULL)
	{
		i = -1;
		while (in->fcmd1[++i] != NULL)
			free (in->fcmd1[i]);
		free (in->fcmd1);
		i = -1;
		while (in->fcmd2[++i] != NULL)
			free (in->fcmd2[i]);
		free (in->fcmd2);
	}
	exit(0);
}*/
