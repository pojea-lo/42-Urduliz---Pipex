#include "pipex.h"

//funcion que abre el archivo de entrada
void    ft_open(t_dat *in)
{
    t_desc  des;//inicio la estructura de descriptores

    des.fds = open ("int_file", O_RDONLY);//descriptor archivo de entrada
    des.fde = open ("ext_file", O_WRONLY);//descriptor archivo de salida
	if (des.fds == -1 || des.fde == -1)//por si hay error de apertuta
	{
		write (1, "Open error\n", 11); 
		ft_free(in);
	}
	if (pipe(des.fd1) == -1)//inicio el pipe y compruebo si hay errores
	{
		write (1, "Pipe error\n", 11);
		ft_free (in);
	}
	des.pidfd1 = fork();//inicio el proceso primero
	if (des.pidfd1 == 0)//hijo primero
	{
		close (des.fd1[0]);
		dup2 (des.fd1[1], STDOUT_FILENO);//para que coja la entrada estandar
		dup2 (des.fds, STDIN_FILENO);
		close (des.fd1[1]);
		close (des.fds);
		execve (in->fcmd1[in->c1], in->cmd1, in->env);
		exit(0);//por si falla que no entre en bucle infinito
	}
	else
	{
		close (des.fd1[1]);
		des.pidfd2 = fork();//inicio el segundo proceso
		if (des.pidfd2 == 0)//hijo segundo
		{
			dup2 (des.fd1[0], STDIN_FILENO); 
			close (des.fd1[0]);
			dup2 (des.fde, STDOUT_FILENO);//para sacarlo por el archivo
			close (des.fde);
			execve (in->fcmd2[in->c2], in->cmd2, in->env);
			exit(0);//por si falla que no entre en bucle infinito
		}
		else
			close (des.fd1[0]);
	}
	waitpid(des.pidfd1, &des.stfd1, 0);
	waitpid(des.pidfd2, &des.stfd2, 0);
	ft_free (in);
	system ("leaks pipex");

}
