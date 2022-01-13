/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaustin <afaustin@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:23:25 by afaustin          #+#    #+#             */
/*   Updated: 2022/01/12 00:23:07 by afaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	**cpy_matrix(char **tmp);
static int	q_strlen(char *str);
static char	*from_to(char *argv, char from, char to);

static char	*from_to(char *argv, char from, char to)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '\'')
		{
			i++;
			while (argv[i] != '\'' && argv[i])
			{
				if (argv[i] == from)
					argv[i] = to;
				i++;
			}
		}
		i++;
	}
	return (argv);
}

static int	q_strlen(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i++;
		j++;
		if (str[i])
			i++;
	}
	return (j);
}

static void	str_remove_quotes(char *quoted_s, char *unquoted_s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (quoted_s[i])
	{
		if (quoted_s[i] == '\'')
			i++;
		unquoted_s[j] = quoted_s[i];
		j++;
		if (quoted_s[i])
			i++;
	}
	unquoted_s[j] = '\0';
}

static char	**cpy_matrix(char **tmp)
{
	int		i;
	char	**result;

	i = 0;
	while (tmp[i])
		i++;
	result = (char **)malloc((i + 1) * sizeof(char *));
	result[i] = NULL;
	i = 0;
	while (tmp[i])
	{
		result[i] = (char *)malloc((q_strlen(tmp[i]) + 1) * sizeof(char));
		str_remove_quotes(tmp[i], result[i]);
		i++;
	}
	return (result);
}

char	**parse_cmd(char *argv)
{
	char	**cmd_splited;
	char	**new_matrix;
	int		i;

	i = 0;
	cmd_splited = ft_split(from_to(argv, ' ', 1), ' ');
	while (cmd_splited[i])
	{
		from_to(cmd_splited[i], 1, ' ');
		i++;
	}
	new_matrix = cpy_matrix(cmd_splited);
	free_matrix(cmd_splited);
	return (new_matrix);
}
