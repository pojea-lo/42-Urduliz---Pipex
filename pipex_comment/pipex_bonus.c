#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_dat	in;

	in.ncmd = argc - 3;
	if (argc < 3)
	{
		write (1, "Argumments error\n", 17);
		return (0);
	}
	else
	{
		in.fs = ft_substr(argv[1], 0, ft_strlen(argv[1]));
		in.fe = ft_substr(argv[argc - 1], 0, ft_strlen(argv[argc - 1]));
		ft_malloc_tri_1 (&in);//hago el malloc de la tridimensiona de cmd
		i = -1;
		while (++i < (argc - 3))//copio los comandos en cmd
			in.cmd[i] = ft_split (argv[i + 2], ' ');
		in.cmd[i] = NULL;
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
	in->aux = ft_split (in->envi, ':');
	free (in->envi);
	i = 0;
	while (in->aux[i] != NULL)
		i++;
	in->env = (char **) malloc (sizeof(char *) * (i + 1));
	if (in->env == NULL)
	{
		perror ("Malloc error");
		ft_free (in);
	}
	i = -1;
	while (in->aux[++i] != 00)
	{
		in->env[i] = ft_strjoin(in->aux[i], "/");
//		printf ("envi: %s\n", in->env[i]);
		free (in->aux[i]);
	}
	in->env[i] = NULL;
//	printf ("envi: %s\n", in->env[i]);
	free (in->aux);
	ft_malloc_tri_2(in);
	ft_join_final(in);
}

void	ft_join_final(t_dat *in)
{
	int		i;
	int		j;

	i = -1;
	while (in->cmd[++i] != NULL)
	{
		j = -1;
		while (in->env[++j] != NULL)
		{
			in->fcmd[i][j] = ft_strjoin(in->env[j], in->cmd[i][0]);
//			printf ("Para i: %d y j: %d -->%s\n", i, j, in->fcmd[i][j]);
		}
		in->fcmd[i][j] = NULL;
	}
	in->fcmd[i] = NULL;
	ft_acces (in);
	ft_open (in);
}

void	ft_acces(t_dat	*in)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (in->fcmd[i] != NULL)
		i++;
	in->c = (int *) malloc (sizeof (int) * (i));
	if (in->c == NULL)
	{
		perror ("Malloc error");
		ft_free (in);
	}
	i = -1;
	while (in->fcmd[++i] != NULL)
	{
		j = -1;
		while (in->fcmd[i][++j] != NULL)
		{
			k = access(in->fcmd[i][j], F_OK);
			if (k == 0)
			{
				in->c[i] = j;
				break ;
			}
		}	
		if (k != 0)
		{
			write (1, "Command error\n", 14);
			ft_free (in);
		}
	}
}
