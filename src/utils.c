/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:34:21 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/01 10:16:56 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}

void	free_and_exit(t_data *data)
{
	if (data->PATH_table)
		free_table(data->PATH_table);
	if (data->cmds)
		free_table(data->cmds);
	if (data->current_command)
		free_table(data->current_command);
	if (data->command_path)
		free(data->command_path);
	if (data)
		free(data);
	exit(errno);
}


void	handle_error(t_data *data, char *msg)
{
	perror(msg);
	free_and_exit(data);
}
static void	complete_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->PATH_table[i])
	{
		temp = data->PATH_table[i];
		data->PATH_table[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
}

void	parsing(t_data *data, int ac, char **av, char **env)
{
	int	i;

	i = 0;
	data->cmds = (char **)malloc(sizeof(char *) * (ac - 2));
	while (i < (ac -3))
	{
		data->cmds[i] = ft_strdup(av[i + 2]);
		i++;
	}
	data->cmds[i] = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			data->PATH = env[i] + 5;
			break;
		}
		i++;
	}
	if (!data->PATH)
		return(handle_error(data, "Error:\nPATH not found in environment"));
	data->PATH_table = ft_split(data->PATH, ':');
	complete_path(data);
}

void	find_program(t_data *data)
{
	int		i;

	i = 0;
	data->current_command = ft_split(data->cmds[data->n_cmd], ' ');
	if (!data->current_command)
		handle_error(data, "Error:\nsplit command failed");
	while (data->PATH_table[i])
	{
		data->command_path = ft_strjoin(data->PATH_table[i], data->current_command[0]);
		if (!access(data->command_path, X_OK))
			break;
		free(data->command_path);
		data->command_path = NULL;
		i++;
	}
	if (!data->command_path)
		return (handle_error(data, "Error:\nCommand directory not found"));
}

void handle_procesess(t_data *data, int prev_pipefd, int *pipefd, char **env)
{
	close(pipefd[0]);
	dup2(prev_pipefd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(prev_pipefd);
	close(pipefd[1]);
	find_program(data);
	if (execve(data->command_path, data->current_command, env) == -1)
		return (handle_error(data, "Error:\nexecve failed"));
	
}
