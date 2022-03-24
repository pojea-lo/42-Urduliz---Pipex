#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write (1, "ERROR\n", 6);
		return (0);
	}
	else
		ft_pipex_error (argv, envp);
	return (0);

}

//funcion que recoge los datos y los analiza con access 
int	ft_pipex_error(char **arg, char **envp)
{
	int		i;
	t_dat	in;//inicio la estructura de datos iniciales

	in.cmd1 = ft_split (arg[2], ' ');
	in.cmd2 = ft_split (arg[3], ' ');
	i = -1;
	while (envp[++i] != 00)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)//busco el PATH del envp
		{
			in.envi = ft_substr (envp[i], 5, (ft_strlen(envp[i]) - 5));//elimino el "PATH=" del envp
			in.fcmd1 = ft_split (in.envi, ':');//guarda las rutas de los binarios (sin la /) - lo guardo de forma temporal en la fcmd1 para luego hacerle un joint y ya dejarlo en la env
			free (in.envi);
			i = 0;
			while (in.fcmd1[i] != NULL)
				i++;
			in.env = (char **) malloc (sizeof(char *) * (i + 1));
			if (in.env == NULL)
			{
//				funcion para liberar
				exit (0);
			}
			i = -1;
			while (in.fcmd1[++i] != NULL)
			{
				in.env[i] = ft_strjoin(in.fcmd1[i], "/");//guardo las rutas de los binarios con /
				free (in.fcmd1[i]);
			}
			in.env[i] = NULL;
			free (in.fcmd1);
			in.fcmd1 = (char **) malloc (sizeof(char *) * (i + 1));
			in.fcmd2 = (char **) malloc (sizeof(char *) * (i + 1));
			i = -1;
			while (in.env[++i] != 00)
			{
				in.fcmd1[i] = ft_strjoin(in.env[i], in.cmd1[0]);
				in.fcmd2[i] = ft_strjoin(in.env[i], in.cmd2[0]);
			}
			in.fcmd1[i] = NULL;
			in.fcmd2[i] = NULL;
			ft_acces (&in);
			return (0);
		}
	}
	return (0);
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
//		meter funcion para liberar
		write (1, "Command error\n", 14); 
		exit (0);
	}
//	printf ("c1: %d / c2: %d\n", in->c1, in->c2);
}
