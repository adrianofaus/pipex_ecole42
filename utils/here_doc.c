/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:29:44 by afaustin          #+#    #+#             */
/*   Updated: 2022/01/13 16:41:30 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	generate_doc(char *limiter, int fd[2]);

t_pipex	set_heredoc(char **argv, char **envp)
{
	t_pipex	data;

	data.limiter = argv[2];
	data.index = 3;
	data.infile = 0;
	data.envp = envp;
	return (data);
}

static void	generate_doc(char *limiter, int fd[2])
{
	int		limiter_size;
	int		bytes_read;
	char	*line;

	limiter_size = ft_strlen(limiter);
	while (1)
	{
		line = ft_calloc((limiter_size + 1), sizeof(char));
		if (!line)
		{
			close_fds(fd);
			exit(EXIT_FAILURE);
		}
		bytes_read = read(STDIN_FILENO, line, limiter_size + 1);
		if (!ft_strncmp(line, limiter, limiter_size))
		{
			free(line);
			close_fds(fd);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, bytes_read);
		free(line);
	}
	close_fds(fd);
	exit(EXIT_FAILURE);
}

void	here_doc(char *limiter)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_put_error("Pipe");
	pid = fork();
	if (pid == -1)
		ft_put_error("Fork");
	if (pid == 0)
		generate_doc(limiter, fd);
	waitpid(pid, NULL, 0);
	dup2_check(fd[0], STDIN_FILENO);
	close_fds(fd);
}
