/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 07:17:04 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/04/13 07:17:07 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open(t_dat *in)
{
	t_desc	des;

	des.fds = open (in->fs, O_RDONLY);
	des.fde = open (in->fe, O_WRONLY | O_CREAT | O_TRUNC, 0764);
	if (des.fds == -1)
	{
		write (1, "Open error\n", 11);
		ft_one (in, &des);
	}
	if (des.fde == -1)
	{
		write (1, "Open error\n", 11);
		ft_free(in);
	}
	if (pipe(des.fd1) == -1)
	{
		write (1, "Pipe error\n", 11);
		ft_free (in);
	}
	ft_fork_1 (in, &des);
}

void	ft_fork_1(t_dat *in, t_desc *des)
{
	des->pidfd1 = fork();
	if (des->pidfd1 == 0)
	{
		ft_close (des->fd1[0]);
		ft_dup2 (des->fd1[1], STDOUT_FILENO, in);
		ft_dup2 (des->fds, STDIN_FILENO, in);
		if (des->fdss == -1)
			ft_close (des->fds);
		ft_close (des->fd1[1]);
		execve (in->fcmd1[in->c1], in->cmd1, in->env);
		exit(0);
	}
	else
	{
		ft_close (des->fd1[1]);
		ft_wait(des->pidfd1, des->stfd1, in);
		ft_fork_2 (in, des);
	}
	ft_free (in);
}

void	ft_fork_2(t_dat *in, t_desc *des)
{
	des->pidfd2 = fork();
	if (des->pidfd2 == 0)
	{
		ft_dup2 (des->fd1[0], STDIN_FILENO, in);
		ft_close (des->fd1[0]);
		ft_dup2 (des->fde, STDOUT_FILENO, in);
		ft_close (des->fde);
		execve (in->fcmd2[in->c2], in->cmd2, in->env);
		exit(0);
	}
	else
	{
		ft_close (des->fd1[0]);
		ft_wait(des->pidfd2, des->stfd2, in);
	}
}

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
}
