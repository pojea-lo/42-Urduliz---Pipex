#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

//start data structure
typedef struct s_dat
{
	int		ncmd;//guarda la cantidad de comandos
	char	*fs;
	char	*fe;
	char	***cmd;
	char	***fcmd;
	char	*envi;
	char	**aux;
	char	**env;
	int		*c;
}	t_dat;

//descriptor structure
typedef struct s_desc
{
	int		fds;
	int		fde;
	int		*fd;
	int		*pidfd;	
	int		*stfd;
	int		fdaux;
}	t_desc;

//pipex_bonus.c
void	ft_free_bi(char **str);
void	ft_malloc_tri_1(int argc, char **argv, t_dat *in);
void	ft_pipex_data(t_dat *in, char *envp);
void	ft_malloc_tri_2(t_dat *in);
void	ft_join_final(t_dat *in);
void	ft_acces(t_dat *in);

//pipex_bonus_utils_0
void	ft_open(t_dat *in);
void	ft_fork_start(t_dat *in, t_desc *des);
void	ft_fork_inter(t_dat *in, t_desc *des, int i);
void	ft_fork_final(t_dat *in, t_desc *des);
void	ft_close(int descr);
void	ft_free(t_dat *in);
void	ft_free_end(t_dat *in);
void	ft_free_des(t_dat *in, t_desc *des);

//split with his static
char	**ft_split(char *s, char c);
int		ft_strlen(char *str);

//str_0 with his static
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_substr(char *s, int start, int len);
int		ft_strlcpy(char *des, char *src, int size);

//str_1
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);

#endif
