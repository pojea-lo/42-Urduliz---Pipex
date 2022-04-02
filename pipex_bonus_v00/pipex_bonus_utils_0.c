#include "pipex_bonus.h"

void	ft_open(t_dat *in)
{
	t_desc	des;

	des.fds = open ("int_file", O_RDONLY);
	des.fde = open ("ext_file", O_WRONLY);
	if (des.fds == -1 || des.fde == -1)
	{
		write (1, "Open error\n", 11);
		ft_free(in);
	}
	des.fd = (int *) malloc (sizeof(int) * 2);
	des.pidfd = (int *) malloc (sizeof (int) * (in->ncmd));
	des.stfd = (int *) malloc (sizeof (int) * (in->ncmd));
	if (des.fd == NULL || des.pidfd == NULL || des.stfd == NULL)
		ft_free_des (in, &des);
	if (pipe(des.fd) == -1)
	{
		write (1, "Pipe error\n", 11);
		ft_free_des (in, &des);
	}
	ft_fork_start (in, &des);
}

//initial fork taking fds like inpunt
void	ft_fork_start(t_dat *in, t_desc *des)
{
	int		i;

	des->pidfd[0] = fork();
	if (des->pidfd[0] == 0)
	{
		ft_close (des->fd[0]);//cierro lect hijo start
		dup2 (des->fd[1], STDOUT_FILENO);
		dup2 (des->fds, STDIN_FILENO);
		ft_close (des->fd[1]);//cierro esc hijo start
		ft_close (des->fds);//cierro archivo entrada
		execve (in->fcmd[0][in->c[0]], in->cmd[0], in->env);
		exit(0);
	}
	else
	{
		ft_close (des->fd[1]);//cierro esc padre start
		waitpid(des->pidfd[0], &des->stfd[0], 0);
		i = 0;//arranco con i = 1 y recibo inform. del pipe fd[0]
		while (++i < (in->ncmd - 1))
		{
			des->fdaux = dup (des->fd[0]);//guardo la salida del pipe en el aux
			ft_close (des->fd[0]);//cierro lect padre
			ft_fork_inter (in, des, i);//inicio el nuevo fork
		}
		ft_fork_final (in, des);
	}
	ft_close (des->fd[0]);
	ft_free_des (in, des);
}

//intermediums forks
void	ft_fork_inter(t_dat *in, t_desc *des, int i)
{
	if (pipe(des->fd) == -1)//regenero el pipe con el mismo fd[0]
	{
		write (1, "Pipe error\n", 11);
		ft_free_des (in, des);
	}
	des->pidfd[i] = fork();//hago el siguiente fork para el proceso
	if (des->pidfd[i] == 0)
	{
		ft_close (des->fd[0]);//cierro lect hijo
		dup2 (des->fd[1], STDOUT_FILENO);
		dup2 (des->fdaux, STDIN_FILENO);//redirijo la entrada al aux
		ft_close (des->fd[1]);//cierro escr hijo
		ft_close (des->fdaux);//cierro el aux del hijo
		execve (in->fcmd[i][in->c[i]], in->cmd[i], in->env);
		exit(0);
	}
	else
	{
		ft_close (des->fd[1]);//cierro escr padre
		ft_close (des->fdaux);//cierro el aux del padre
	}
	waitpid (des->pidfd[i], &des->stfd[i], 0);
}

//final fork taking fde like exit
void	ft_fork_final(t_dat *in, t_desc *des)
{
	des->pidfd[in->ncmd - 1] = fork();
	if (des->pidfd[in->ncmd - 1] == 0)
	{
//		ft_close (des->fd[1]);//pq? me da Bad descriptor
		dup2 (des->fd[0], STDIN_FILENO);
		ft_close (des->fd[0]);
		dup2 (des->fde, STDOUT_FILENO);
		ft_close (des->fde);
		execve (in->fcmd[in->ncmd - 1][in->c[in->ncmd - 1]], in->cmd[in->ncmd - 1], in->env);
		exit(0);
	}
	else
//		ft_close (des->fd[0]);//pq? me da Bad  descriptor
		waitpid (des->pidfd[in->ncmd - 1], &des->stfd[in->ncmd - 1], 0);
}

void	ft_close(int descr)
{
	int	i;

	i = 0;
	if (descr != 0 && descr != 1 && descr != 2)
		i = close (descr);
	if (i == -1)
		perror ("Close error");//hay que salir del programa en los waitpids con el status POR HACER!!!
}

void	ft_free(t_dat *in)
{
	int	i;
	int	j;

	if (in->cmd != NULL)
	{
		i = -1;
		while (in->cmd[++i] != NULL)
		{
			j = -1;
			while (in->cmd[i][++j] != NULL)
				free(in->cmd[i][j]);
			free(in->cmd[i]);
		}
		free (in->cmd);
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
	int	j;

	if (in->fs != NULL)
		free (in->fs);
	if (in->fe != NULL)
		free (in->fe);
	if (in->fcmd != NULL)
	{
		i = -1;
		while (in->fcmd[++i] != NULL)
		{
			j = -1;
			while (in->fcmd[i][++j] != NULL)
				free (in->fcmd[i][j]);
			free (in->fcmd[i]);
		}
		free (in->fcmd);
	}
	if (in->c != NULL)
		free (in->c);
	system ("leaks pipex_bonus");
	exit(0);
}

void	ft_free_des(t_dat *in, t_desc *des)
{
	if (des->fd != NULL)
	{
		printf ("libero fd"); 
		free (des->fd);
	}
	if (des->pidfd != NULL)
	{
		printf ("libero pidfd"); 
		free (des->pidfd);
	}
	if (des->stfd != NULL)
	{
		printf ("libero stfd"); 
		free (des->stfd);
	ft_free (in);
}
