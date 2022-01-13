/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 20:03:07 by afaustin          #+#    #+#             */
/*   Updated: 2022/01/12 13:07:19 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static char	**get_paths(char **envp);

static char	**get_paths(char **envp)
{
	char	*env_paths;
	char	**all_paths;
	int		i;

	i = 0;
	env_paths = NULL;
	while (envp[i] && env_paths == NULL)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			env_paths = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		i++;
	}
	if (env_paths != NULL)
	{
		all_paths = ft_split(env_paths, ':');
		free(env_paths);
		return (all_paths);
	}
	return (0);
}

static char	*check_access(t_pipex *data, char **command)
{
	char	*cmd_path;
	char	*full_path;
	int		i;

	i = 0;
	data->env_paths = get_paths(data->envp);
	cmd_path = ft_strjoin("/", command[0]);
	full_path = ft_strjoin(data->env_paths[i], cmd_path);
	while (data->env_paths[i])
	{
		if (access(full_path, F_OK) == 0)
		{
			free(cmd_path);
			free_matrix(data->env_paths);
			return (full_path);
		}
		i++;
		free(full_path);
		full_path = ft_strjoin(data->env_paths[i], cmd_path);
	}
	free(cmd_path);
	free(full_path);
	free_matrix(data->env_paths);
	return (NULL);
}

void	try_cmd(char *argv, t_pipex *data)
{
	char	**cmd;
	int		i;
	char	*valid_path;

	i = 0;
	cmd = parse_cmd(argv);
	if (!cmd[0])
	{
		free_matrix(cmd);
		exit(126);
	}
	valid_path = check_access(data, cmd);
	if (valid_path == NULL || execve(valid_path, cmd, data->envp) == -1)
	{
		perror(cmd[0]);
		free(valid_path);
		free_matrix(cmd);
		exit(127);
	}
}

void	create_connection(char	*argv, t_pipex *data)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_put_error("Pipe");
	pid = fork();
	if (pid == -1)
		ft_put_error("Fork");
	if (pid == 0)
	{
		if (data->infile == -1)
		{
			close_fds(fd);
			exit(0);
		}
		dup2_check(fd[1], STDOUT_FILENO);
		close_fds(fd);
		try_cmd(argv, data);
	}
	dup2_check(fd[0], STDIN_FILENO);
	close_fds(fd);
	waitpid(pid, NULL, WNOHANG);
}
