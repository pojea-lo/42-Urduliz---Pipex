/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 06:41:46 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/04/13 07:33:37 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	res = waitpid(pid, &st, 0);
	if (res == -1)
	{
		perror ("Waitpid error");
		ft_free (in);
	}
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

//function to run program without int_file
void	ft_one(t_dat *in, t_desc *des)
{
	des->fds = open (in->fs, O_RDONLY | O_CREAT, 0764);
	if (des->fds == -1)
		ft_free(in);
	des->pidfd2 = fork();
	if (des->pidfd2 == 0)
	{
		dup2(des->fds, STDIN_FILENO);
		ft_close (des->fds);
		dup2(des->fde, STDOUT_FILENO);
		ft_close (des->fde);
		ft_rm (in, des);
		execve (in->fcmd2[in->c2], in->cmd2, in->env);
		exit(0);
	}
	ft_wait(des->pidfd2, des->stfd2, in);
	ft_free (in);
}

//function to erase the inter file in case it does exist
void	ft_rm(t_dat *in, t_desc *des)
{
	char	*rm[3];

	rm[0] = "rm";
	rm[1] = in->fs;
	rm[2] = NULL;
	des->pidfd1 = fork();
	if (des->pidfd1 == 0)
		execve ("/bin/rm", rm, in->env);
	ft_wait(des->pidfd1, des->stfd1, in);
}
