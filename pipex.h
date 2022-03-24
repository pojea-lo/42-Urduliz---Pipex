#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//estructura para todos los datos iniciales
typedef struct	s_dat
{
	char	**cmd1;//guarda el cmd1 con sus argumentos
	char	**fcmd1;//guarda el cmd1 (sin argu) con todas las rutas del PATH
	char	**cmd2;//guarda el cmd2 con sus argumentos
	char	**fcmd2;//guarda el cmd2 (sin argu) con todas las rutas del PATH
	char	*envi;//cadena que guarda el "PATH=..."
	char	**env;//guarga las cadenas de las rutas
	int		c1;//guarda la posicion de la carpeta del env donde existe el comd1
	int		c2;//guarda la posicion de la carpeta del env donde existe el comd2
}	t_dat;

//functions of pipex.c
int		ft_pipex_error(char **arg, char **envp);
void	ft_acces(t_dat *in);

//split
char	**ft_split(char *s, char c);
//static char	*ft_copy(char const *s, int i, int j);
//static int	ft_count(char const *s, char c);
//static char	**ft_malloc(char const *s, char c);
int		ft_strlen(char *str);

//str
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_substr(char *s, int start, int len);
//static	char	*ft_malloc(char *s, int start, int len);
int		ft_strlcpy(char *des, char *src, int size);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);

#endif
