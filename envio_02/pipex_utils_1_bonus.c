/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 07:09:38 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/04/06 07:09:40 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	res = waitpid(pid, &st, WNOHANG);
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

void	ft_malloc_c(t_dat *in)
{
	int	i;

	i = 0;
	while (in->fcmd[i] != NULL)
		i++;
	in->c = (int *) malloc (sizeof (int) * (i));
	if (in->c == NULL)
	{
		perror ("Malloc error");
		ft_free (in);
	}
}
