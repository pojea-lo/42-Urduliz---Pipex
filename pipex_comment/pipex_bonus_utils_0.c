#include "pipex_bonus.h"

//start of all process
void	ft_open(t_dat *in)
{
	t_desc	des;//inicio la estructura para descripores
	des.fds = open ("int_file", O_RDONLY);//abro archivo de entrada
	des.fde = open ("ext_file", O_WRONLY, O_TRUNC);//abro archivo de salida
	if (des.fds == -1 || des.fde == -1) //control de errores de apertura
	{
		write (1, "Open error\n", 11);
		ft_free(in);
	}
	des.pidfd = (int *) malloc (sizeof (int) * (in->ncmd));//malloc del array de pids
	des.stfd = (int *) malloc (sizeof (int) * (in->ncmd));//malloc del array de status
	if (des.pidfd == NULL || des.stfd == NULL)
	{
		perror ("Malloc error");
		ft_free_des (in, &des);
	}
	if (in->ncmd > 1)//condicion para cuando metan mas de un comando
	{
		if (pipe(des.fd) == -1) //inicio la primera pipe
		{
			perror("Pipe error");
			ft_free_des (in, &des);
		}
		ft_fork_start (in, &des);
	}
	else//condicion cuando me meten 1 comando solo
		ft_fork_final_one (in, &des);
}

//initial fork taking fds like inpunt
void	ft_fork_start(t_dat *in, t_desc *des)
{
	int		i;

	ft_fork (in, des, 0);
	if (des->pidfd[0] == 0)
	{
		ft_close (des->fd[0]);//cierro lect hijo start
		ft_dup2 (des->fd[1], STDOUT_FILENO, in, des);
		ft_dup2 (des->fds, STDIN_FILENO, in, des);
		ft_close (des->fd[1]);//cierro esc hijo start
		ft_close (des->fds);//cierro archivo entrada
		execve (in->fcmd[0][in->c[0]], in->cmd[0], in->env);
		exit(0);
	}
	else
	{
		ft_close (des->fd[1]);//cierro esc padre start
		ft_wait(des->pidfd[0], des->stfd[0], in, des);
		i = 0;//arranco con i = 1 y recibo inform. del pipe fd[0]
		while (++i < (in->ncmd - 1))
			ft_fork_inter (in, des, i);//inicio el nuevo fork
		ft_fork_final (in, des);
	}
	ft_close (des->fd[0]);
	ft_free_des (in, des);
}

//intermediums forks
void	ft_fork_inter(t_dat *in, t_desc *des, int i)
{
	des->fdaux = dup (des->fd[0]);//guardo la salida del pipe en el aux
	ft_close (des->fd[0]);//cierro lect padre
	if (pipe(des->fd) == -1) //regenero el pipe con el mismo fd[0]
	{
		perror ("Pipe error");
		ft_free_des (in, des);
	}
	ft_fork (in, des, i);//hago el siguiente fork del proceso
	if (des->pidfd[i] == 0)
	{
		ft_close (des->fd[0]);//cierro lect hijo
		ft_dup2 (des->fd[1], STDOUT_FILENO, in, des);
		ft_dup2 (des->fdaux, STDIN_FILENO, in, des);//redirijo la entrada al aux
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
	ft_wait (des->pidfd[i], des->stfd[i], in, des);
}

//final fork taking fde like exit
void	ft_fork_final(t_dat *in, t_desc *des)
{
	ft_fork (in, des, in->ncmd - 1);//hago el utlimo fork del programa
	if (des->pidfd[in->ncmd - 1] == 0)
	{
//		ft_close (des->fd[1]);//pq? me da Bad descriptor
		ft_dup2 (des->fd[0], STDIN_FILENO, in, des);
		ft_close (des->fd[0]);
		ft_dup2 (des->fde, STDOUT_FILENO, in, des);
		ft_close (des->fde);
		execve (in->fcmd[in->ncmd - 1][in->c[in->ncmd - 1]], in->cmd[in->ncmd - 1], in->env);
		exit(0);
	}
	else
//		ft_close (des->fd[0]);//pq? me da Bad  descriptor
		ft_wait (des->pidfd[in->ncmd - 1], des->stfd[in->ncmd - 1], in, des);
}

void	ft_fork_final_one(t_dat *in, t_desc *des)
{
	ft_fork (in, des, 0);//hago el utlimo fork del programa
	if (des->pidfd[0] == 0)
	{
		ft_dup2 (des->fds, STDIN_FILENO, in, des);
		ft_close (des->fds);
		ft_dup2 (des->fde, STDOUT_FILENO, in, des);
		ft_close (des->fde);
		execve (in->fcmd[0][in->c[0]], in->cmd[0], in->env);
	}
	else
		ft_wait (des->pidfd[0], des->stfd[0], in, des);
	ft_free_des (in, des);
}
