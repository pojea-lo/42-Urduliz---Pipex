#include "pipex.h"

//funcion que abre el archivo de entrada
void    ft_open(t_dat *in)
{
    t_desc  des;//inicio la estructura de descriptores

	printf ("la prim ruta es: %s y el cmd es: %d\n", in->fcmd1[in->c1], in->c1);
	printf ("la segu ruta es: %s y el cmd es: %d\n", in->fcmd2[in->c2], in->c2);
    des.fds = open (in->fs, O_RDONLY);//descriptor archivo de entrada
    des.fde = open (in->fe, O_WRONLY);//descriptor archivo de salida
	if (des.fds == -1)//por si hay error de apertuta
		ft_free(in);
	if (pipe(des.fd1) == -1)//inicio el pipe
	{
		write (1, "Pipe error\n", 11);
		ft_free (in);
	}
	des.pidfd1 = fork();//inicio el proceso primero
	if (des.pidfd1 == 0)//hijo primero
	{
		close (des.fd1[0]);
		dup2 (des.fd1[1], des.fds);
		dup2 (des.fd1[1], 1); 
		close (des.fd1[1]);
		close (des.fds);
		execve (in->fcmd1[in->c1], in->cmd1, in->env);
		exit(0);
	}
	des.pidfd2 = fork();//inicio el segundo proceso
	if (des.pidfd2 == 0)//hijo segundo
	{
		close (des.fd1[1]);
		dup2 (des.fd1[0], 0); 
		dup2 (des.fde, STDOUT_FILENO);//, des.fd1[0]);
		close (des.fd1[0]);
		close (des.fde);
		execve (in->fcmd2[in->c2], in->cmd2, in->env);
	}
	waitpid(des.pidfd1, &des.stfd1, 0);
	printf ("LISTO, el primer proceso hecho\n");
	waitpid(des.pidfd2, &des.stfd2, 0);
	printf ("LISTO, el segundo proceso hecho\n");
}
