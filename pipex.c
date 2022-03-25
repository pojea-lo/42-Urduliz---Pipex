#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_dat	in;//inicio la estructura de datos iniciales
	
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
			if (ft_strncmp(envp[i], "PATH", 4) == 0)//busco el PATH del envp
				ft_pipex_data (&in, envp[i]);
		}
	}
	return (0);
}

//funcion que recoge y compone las cadenas de datos 
void	ft_pipex_data(t_dat *in, char *envp)
{
	int		i;

	in->envi = ft_substr (envp, 5, (ft_strlen(envp) - 5));//elimino el "PATH=" del envp
	in->fcmd1 = ft_split (in->envi, ':');//guarda las rutas de los binarios (sin la /) - lo guardo de forma temporal en la fcmd1 para luego hacerle un joint y ya dejarlo en la env
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
		in->env[i] = ft_strjoin(in->fcmd1[i], "/");//guardo las rutas de los binarios con /
		free (in->fcmd1[i]);
	}
	in->env[i] = NULL;
	free (in->fcmd1);
	in->fcmd1 = (char **) malloc (sizeof(char *) * (i + 1));
	in->fcmd2 = (char **) malloc (sizeof(char *) * (i + 1));
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

//función que analiza los comandos
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

//funcion que libera a la salida y sale del programa
void	ft_free(t_dat *in)
{
	int	i;

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

//continuación de la ft_free
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
