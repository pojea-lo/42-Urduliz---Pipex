/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 07:10:08 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/04/06 07:10:10 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_des(t_dat *in, t_desc *des)
{
	if (des->pidfd != NULL)
		free (des->pidfd);
	if (des->stfd != NULL)
		free (des->stfd);
	ft_free (in);
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
	exit(0);
}

void	ft_malloc_tri_1(t_dat *in)
{
	in->cmd = (char ***) malloc (sizeof(char *) * (in->ncmd + 1));
	if (in->cmd == NULL)
	{
		perror ("Malloc error");
		ft_free (in);
	}
}

void	ft_malloc_tri_2(t_dat *in)
{
	int		i;
	int		c;

	c = 0;
	while (in->env[c] != NULL)
		c++;
	in->fcmd = (char ***) malloc (sizeof(char *) * (in->ncmd + 1));
	if (in->fcmd == NULL)
	{
		perror ("Malloc error");
		ft_free(in);
	}
	i = -1;
	while (++i < in->ncmd)
	{
		in->fcmd[i] = (char **) malloc (sizeof(char *) * (c + 1));
		if (in->fcmd[i] == NULL)
		{
			perror ("Malloc error");
			ft_free (in);
		}
	}
}
