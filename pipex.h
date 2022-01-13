/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:35:42 by afaustin          #+#    #+#             */
/*   Updated: 2022/01/12 01:12:41 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int			infile;
	int			outfile;
	int			index;
	char		*limiter;
	char		**envp;
	char		**env_paths;
}	t_pipex;

/*LIBFT Functions*/
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(const char *s, char c);
char	*ft_strdup(char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nelem, size_t elsize);
void	ft_bzero(void *s, size_t n);

/*Aditional functions*/
char	**parse_cmd(char *argv);
void	ft_put_error(char *str);
void	here_doc(char *limiter);
void	pipex(t_pipex *data, int argc, char **argv);
void	dup2_check(int fd1, int fd2);
void	create_connection(char	*argv, t_pipex *data);
void	try_cmd(char *argv, t_pipex *data);
void	free_matrix(char **paths);
void	close_fds(int *fd);
t_pipex	set_heredoc(char **argv, char **envp);

#endif