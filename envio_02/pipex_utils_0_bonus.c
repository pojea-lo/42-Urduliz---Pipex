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

	des.fds = open ("int_file", O_RDONLY);
	des.fde = open ("ext_file", O_WRONLY, O_TRUNC);
	if (des.fds == -1 || des.fde == -1)
		ft_free(in);
	des.pidfd = (int *) malloc (sizeof (int) * (in->ncmd));
	des.stfd = (int *) malloc (sizeof (int) * (in->ncmd));
	if (des.pidfd == NULL || des.stfd == NULL)
	{
		perror ("Malloc error");
		ft_free_des (in, &des);
	}
	if (in->ncmd > 1)
	{
		if (pipe(des.fd) == -1)
		{
			perror("Pipe error");
			ft_free_des (in, &des);
		}
		ft_fork_start (in, &des);
	}
	else
		ft_fork_final_one (in, &des);
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
	des->fdaux = dup (des->fd[0]);
	ft_close (des->fd[0]);
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

void	ft_fork_final_one(t_dat *in, t_desc *des)
{
	ft_fork (in, des, 0);
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
