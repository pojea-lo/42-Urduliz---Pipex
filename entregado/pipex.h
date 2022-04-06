/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pojea-lo <pojea-lo@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 07:22:50 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/04/06 06:44:00 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

//start data structure
typedef struct s_dat
{
	char	*fs;
	char	*fe;
	char	**cmd1;
	char	**fcmd1;
	char	**cmd2;
	char	**fcmd2;
	char	*envi;
	char	**env;
	int		c1;
	int		c2;
}	t_dat;

//descriptor structure
typedef struct s_desc
{
	int		fds;
	int		fde;
	int		fd1[2];
	int		pidfd1;	
	int		pidfd2;
	int		stfd1;
	int		stfd2;
}	t_desc;

//pipex.c
void	ft_pipex_data(t_dat *in, char *envp);
void	ft_join_final(t_dat *in);
void	ft_acces(t_dat *in);

//pipex_utils_0
void	ft_open(t_dat *in);
void	ft_fork_1(t_dat *in, t_desc *des);
void	ft_fork_2(t_dat *in, t_desc *des);
void	ft_free(t_dat *in);
void	ft_free_end(t_dat *in);

//pipex_utils_1
void	ft_close(int descr);
void	ft_wait(int pid, int st, t_dat *in);
void	ft_dup2(int desold, int desnew, t_dat *in);

//split with his static
char	**ft_split(char *s, char c);
int		ft_strlen(char *str);

//ft_str_0 with his static
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_substr(char *s, int start, int len);
int		ft_strlcpy(char *des, char *src, int size);

//ft_str_1
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);

#endif
