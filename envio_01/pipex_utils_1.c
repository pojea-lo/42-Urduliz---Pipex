/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 06:41:46 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/04/06 06:42:11 by pojea-lo         ###   ########.fr       */
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

//execve function with error control


//function to erase the inter file in case it does exist
void	ft_rm(t_dat *in, t_desc *des)
{
	char	*rm[3];

	rm[0] = "rm";
	rm[1] = in->fs;
	rm[2] = NULL;
	des->pidfd1 = fork();
	if (des->pidfd1 == 0)
	{
		ft_close (des->fds);
		execve ("/bin/rm", rm, in->env);
	}
	ft_wait(des->pidfd1, des->stfd1, in);
}
