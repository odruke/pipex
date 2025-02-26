/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:34:21 by odruke-s          #+#    #+#             */
/*   Updated: 2025/02/26 22:02:43 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i]);
	free(table);
}

void	free_and_exit(data);
{
	if (data->cmds)
		free_table(data->cmds);
	if (data->PATH_table)
		free_table(data->PATH_table);
	
}


void	handle_error(char *msg)
{
	perror(msg);
	free_and_exit(data);
	exit(errno);
}

void	parsing(t_data *data, int ac, char **av, char **env)
{
	int	i;

	i = 0;
	data->cmds = (char **)malloc(sizeof(char *) * (ac - 2));
	while (i < (ac -3))
	{
		data->cmds[i] = ft_strdup(av[i + 2])
		i++;
	}
	data->cmds[i] == NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], "PATH=" 5))
		{
			data->PATH = env[i] + 5;
			break;
		}
		i++;
	}
	if (!data->PATH)
		error_handle(data, "Error:\nPATH not found in environment\n");
	data->PATH_table = ft_split(data->PATH, ':');
}

void	find_program(t_data *data)
{
	char	**current_command;
	char	*command_path;
	int		i;

	i = 0;
	current_command = ft_split(data->cmds[n_cmd], ' ');
	command_path = NULL;
	while (data->PATH[i])
	{
		command_path = ft_strjoin(data->PATH[i], current_command[0]);
		if (!access(command_path, X_OK))
			return (command_path);
		free(command_path);
	}
}

void handle_procesess(t_data *data, int infile_fd, int *pipefd)
{
	char	*cmd[2] = {"cat", NULL};

	close(pipefd[0]);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(infile_fd);
	close(pipefd[1]);
	if (execve("/usr/bin/cat", cmd, env) == -1)
		handle_error(data, "Error:\nexecve failed\n");
	exit(errno);
}
