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
		ft_malloc_tri_1 (argc, argv, &in);//hago el malloc de la tridimensiona de cmdl
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

void	ft_free_bi(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != NULL)
		i++;
	printf ("la i da:%d\n", i);
	j = 0;
	while (j <= i)
	{
		free (str[j]);
		j++;
	}
	free (str);
}

void	ft_malloc_tri_1(int argc, char **argv, t_dat *in)
{
	int	i;
	int	j;
	int	k;

	in->cmd = (char ***) malloc (sizeof(char *) * (in->ncmd + 1));
	if (in->cmd == NULL)
	{
		ft_free (in);
		exit (0);
	}
	i = 0;
	while (i < in->ncmd)
	{
		j = 2;
		while (j < (argc - 1))
		{
			in->aux = ft_split (argv[j], ' ');
			k = 0;
			while (in->aux[k] != NULL)
			{
				free (in->aux[k]);
				k++;
			}
			free (in->aux);
//			ft_free_bi (in->aux);
			in->cmd[i] = (char **) malloc (sizeof(char *) * (k + 1));
			if (in->cmd[i] == NULL)
			{
				ft_free (in);
				exit (0);
			}
			j++;
		}
		i++;
	}
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
		ft_free (in);
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

void	ft_malloc_tri_2(t_dat *in)
{
	int		i;
//	int		j;
	int		c;//cantidad de comandos

	c = 0;
	while (in->env[c] != NULL)//cuento los enviroment
		c++;
//	printf ("la e da: %d y la c da: %d\n", e, c);
	in->fcmd = (char ***) malloc (sizeof(char *) * (in->ncmd + 1));
	if (in->fcmd == NULL)
		ft_free(in);
	i = 0;
	while (i < in->ncmd)
	{
		in->fcmd[i] = (char **) malloc (sizeof(char *) * (c + 1));
		if (in->fcmd[i] == NULL)
			ft_free (in);
		i++;
	}
}

void	ft_join_final(t_dat *in)
{
	int		i;
	int		j;

	i = 0;
	while (in->cmd[i] != NULL)
	{
		j = 0;
		while (in->env[j] != NULL)
		{
			in->fcmd[i][j] = ft_strjoin(in->env[j], in->cmd[i][0]);
//			printf ("Para i: %d y j: %d -->%s\n", i, j, in->fcmd[i][j]);
			j++;
		}
		in->fcmd[i][j] = NULL;
		i++;
	}
	in->fcmd[i] = NULL;
	ft_acces (in);
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
		ft_free (in);
	i = 0;
	while (in->fcmd[i] != NULL)
	{
		j = 0;
		while (in->fcmd[i][j] != NULL)
		{
			k = access(in->fcmd[i][j], F_OK);
			if (k == 0)
			{
				in->c[i] = j;
//				printf ("El comando i: %d que es: %s tiene una c[i]: %d\n", i, in->fcmd[i][j], in->c[i]);
				break;
			}
			j++;
		}	
		if (k != 0)
		{
			write (1, "Command error\n", 14);
			ft_free (in);
		}
		i++;
	}
	ft_open (in);
}
