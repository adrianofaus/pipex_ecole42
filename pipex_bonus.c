/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:08:16 by afaustin          #+#    #+#             */
/*   Updated: 2022/01/12 13:08:17 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup2_check(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd1);
}

void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	pipex(t_pipex *data, int argc, char **argv)
{
	while (data->index < argc - 2)
	{
		create_connection(argv[data->index], data);
		data->index++;
	}
	if (data->outfile == -1)
		exit(EXIT_FAILURE);
	dup2_check(data->outfile, STDOUT_FILENO);
	try_cmd(argv[argc - 2], data);
}

t_pipex	set_pipex(int argc, char **argv, char **envp)
{
	t_pipex	data;

	data.index = 2;
	data.infile = open(argv[1], O_RDONLY);
	data.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	data.envp = envp;
	if (data.infile != -1)
		dup2_check(data.infile, STDIN_FILENO);
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		out;

	if (argc < 5)
	{
		perror("Args");
		exit(0);
	}
	if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 8) && argv[1][8] == '\0')
	{
		data = set_heredoc(argv, envp);
		here_doc(data.limiter);
		out = argc - 1;
		data.outfile = open(argv[out], O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	else if (argc >= 5)
		data = set_pipex(argc, argv, envp);
	pipex(&data, argc, argv);
	return (0);
}
