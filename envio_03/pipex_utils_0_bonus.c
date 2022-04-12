/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 07:09:00 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/04/06 07:09:03 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

//start of all process
void	ft_open(t_dat *in)
{
	t_desc	des;

	des.pidfd = (int *) malloc (sizeof (int) * (in->ncmd));
	des.stfd = (int *) malloc (sizeof (int) * (in->ncmd));
	des.bol = 0;
	if (des.pidfd == NULL || des.stfd == NULL)
	{
		perror ("Malloc error");
		ft_free_des (in, &des);
	}
	des.fds = open (in->fs, O_RDONLY);
	des.fde = open (in->fe, O_WRONLY|O_CREAT|O_TRUNC, 0764);
	if (des.fde == -1)
	{
		write (1, "Open error\n", 11);
		ft_free(in);
	}
	if (des.fds == -1)
	{
		write (1, "Open error\n", 11);
		ft_one (in, &des);
	}
	if (pipe(des.fd) == -1)
	{
		perror("Pipe error");
		ft_free_des (in, &des);
	}
	ft_fork_start (in, &des);
}

//initial fork taking fds like inpunt
void	ft_fork_start(t_dat *in, t_desc *des)
{
	int		i;

	ft_fork (in, des, 0);
	if (des->pidfd[0] == 0)
	{
		ft_close (des->fd[0]);
		ft_dup2 (des->fd[1], STDOUT_FILENO, in, des);
		ft_dup2 (des->fds, STDIN_FILENO, in, des);
		ft_close (des->fd[1]);
		ft_close (des->fds);
		execve (in->fcmd[0][in->c[0]], in->cmd[0], in->env);
		exit(0);
	}
	else
	{
		ft_close (des->fd[1]);
		ft_wait(des->pidfd[0], des->stfd[0], in, des);
		i = 0;
		while (++i < (in->ncmd - 1))
			ft_fork_inter (in, des, i);
		ft_fork_final (in, des);
	}
	ft_close (des->fd[0]);
	ft_free_des (in, des);
}

//intermediums forks
void	ft_fork_inter(t_dat *in, t_desc *des, int i)
{
	if (des->bol == 0)
	{
		des->fdaux = dup (des->fd[0]);
		ft_close (des->fd[0]);
	}
	if (pipe(des->fd) == -1)
	{
		perror ("Pipe error");
		ft_free_des (in, des);
	}
	ft_fork (in, des, i);
	if (des->pidfd[i] == 0)
	{
		ft_close (des->fd[0]);
		ft_dup2 (des->fd[1], STDOUT_FILENO, in, des);
		ft_dup2 (des->fdaux, STDIN_FILENO, in, des);
		ft_close (des->fd[1]);
		ft_close (des->fdaux);
		execve (in->fcmd[i][in->c[i]], in->cmd[i], in->env);
		exit(0);
	}
	else
	{
		ft_close (des->fd[1]);
		ft_close (des->fdaux);
	}
	ft_wait (des->pidfd[i], des->stfd[i], in, des);
}

//final fork taking fde like exit
void	ft_fork_final(t_dat *in, t_desc *des)
{
	ft_fork (in, des, in->ncmd - 1);
	if (des->pidfd[in->ncmd - 1] == 0)
	{
		ft_dup2 (des->fd[0], STDIN_FILENO, in, des);
		ft_close (des->fd[0]);
		ft_dup2 (des->fde, STDOUT_FILENO, in, des);
		ft_close (des->fde);
		execve (in->fcmd[in->ncmd - 1][in->c[in->ncmd - 1]], \
		in->cmd[in->ncmd - 1], in->env);
		exit(0);
	}
	else
		ft_wait (des->pidfd[in->ncmd - 1], des->stfd[in->ncmd - 1], in, des);
}

//function to run program without int_file
void	ft_one(t_dat *in, t_desc *des)
{
	int	i;
	
	des->bol = -1;
	des->fds = open (in->fs, O_RDONLY|O_CREAT, 0764);
	if (des->fds == -1)
		ft_free(in);
	ft_dup2 (STDIN_FILENO, des->fdaux, in, des);
	ft_rm (in, des);
	i = 0;
	while (++i < (in->ncmd - 1))
		ft_fork_inter (in, des, i);
	ft_fork_final (in, des);
	ft_close (des->fd[0]);
	ft_free_des (in, des);
}

//function to erase the inter file in case it does exist
void	ft_rm(t_dat *in, t_desc *des)
{
	char	*rm[3];

	rm[0] = "rm";
	rm[1] = in->fs;
	rm[2] = NULL;
	des->pidfd[0] = fork();
	if (des->pidfd[0] == 0)
	{
//		ft_close (des->fds);
		execve ("/bin/rm", rm, in->env);
	}
	ft_wait(des->pidfd[0], des->stfd[0], in, des);
}