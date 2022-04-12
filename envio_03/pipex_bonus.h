/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 07:10:50 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/04/06 07:11:03 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

//start data structure
typedef struct s_dat
{
	int		ncmd;
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
	int		fd[2];
	int		*pidfd;	
	int		*stfd;
	int		fdaux;
	int		bol;
}	t_desc;

//pipex_bonus.c
void	ft_pipex_data(t_dat *in, char *envp);
void	ft_join_final(t_dat *in);
void	ft_acces(t_dat *in);

//pipex_bonus_utils_0
void	ft_open(t_dat *in);
void	ft_fork_start(t_dat *in, t_desc *des);
void	ft_fork_inter(t_dat *in, t_desc *des, int i);
void	ft_fork_final(t_dat *in, t_desc *des);
void	ft_one(t_dat *in, t_desc *des);
void	ft_rm(t_dat *in, t_desc *des);

//pipex_bonus_utils_1
void	ft_close(int descr);
void	ft_wait(int pid, int st, t_dat *in, t_desc *des);
void	ft_fork(t_dat *in, t_desc *des, int i);
void	ft_dup2(int desold, int desnew, t_dat *in, t_desc *des);
void	ft_malloc_c(t_dat *in);

//pipex_bonus_utils_1
void	ft_free(t_dat *in);
void	ft_free_end(t_dat *in);
void	ft_free_des(t_dat *in, t_desc *des);
void	ft_malloc_tri_1(t_dat *in);
void	ft_malloc_tri_2(t_dat *in);

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
