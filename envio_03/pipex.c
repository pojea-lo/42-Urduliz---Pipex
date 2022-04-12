/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:15:54 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/03/29 07:10:27 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_dat	in;

	if (argc != 5)
	{
		write (1, "Argumments error\n", 17);
		return (0);
	}
	else
	{
		in.fs = ft_substr(argv[1], 0, ft_strlen(argv[1]));
		in.fe = ft_substr(argv[4], 0, ft_strlen(argv[4]));
		in.cmd1 = ft_split (argv[2], ' ');
		in.cmd2 = ft_split (argv[3], ' ');
		i = -1;
		while (envp[++i] != 00)
		{
			if (ft_strncmp(envp[i], "PATH", 4) == 0)
				ft_pipex_data (&in, envp[i]);
		}
	}
	return (0);
}

void	ft_pipex_data(t_dat *in, char *envp)
{
	int		i;

	in->envi = ft_substr (envp, 5, (ft_strlen(envp) - 5));
	in->fcmd1 = ft_split (in->envi, ':');
	free (in->envi);
	i = 0;
	while (in->fcmd1[i] != NULL)
		i++;
	in->env = (char **) malloc (sizeof(char *) * (i + 1));
	if (in->env == NULL)
		ft_free (in);
	i = -1;
	while (in->fcmd1[++i] != NULL)
	{
		in->env[i] = ft_strjoin(in->fcmd1[i], "/");
		free (in->fcmd1[i]);
	}
	in->env[i] = NULL;
	free (in->fcmd1);
	in->fcmd1 = (char **) malloc (sizeof(char *) * (i + 1));
	in->fcmd2 = (char **) malloc (sizeof(char *) * (i + 1));
	ft_join_final(in);
}

void	ft_join_final(t_dat *in)
{
	int		i;

	i = -1;
	while (in->env[++i] != 00)
	{
		in->fcmd1[i] = ft_strjoin(in->env[i], in->cmd1[0]);
		in->fcmd2[i] = ft_strjoin(in->env[i], in->cmd2[0]);
	}
	in->fcmd1[i] = NULL;
	in->fcmd2[i] = NULL;
	ft_acces (in);
}

void	ft_acces(t_dat	*in)
{
	int	i;
	int	j;

	in->c1 = -1;
	in->c2 = -1;
	i = -1;
	while (in->fcmd1[++i] != NULL)
	{
		j = access(in->fcmd1[i], F_OK);
		if (j == 0)
			in->c1 = i;
		j = access(in->fcmd2[i], F_OK);
		if (j == 0)
			in->c2 = i;
	}
	if (in->c1 == -1 || in->c2 == -1)
	{
		write (1, "Command error\n", 14);
		ft_free (in);
	}
	ft_open (in);
}
