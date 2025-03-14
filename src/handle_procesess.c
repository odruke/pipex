/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_procesess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:10:49 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/11 19:54:50 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_procesess(t_data *data, char **env)
{
	errno = 0;
	if (!data->current_command[0])
		handle_error(data, "", "permission denied", 1);
	else if (!data->command_path)
	{
		free_data(data);
		exit(127);
	}
	else if (data->fds->prev_pipe < 1)
	{
		free_data(data);
		exit(0);
	}
	close(data->fds->pipefd[0]);
	if (dup2(data->fds->prev_pipe, STDIN_FILENO) == -1)
		handle_error(data, "", "Error:\ndup2 failed", 1);
	if (dup2(data->fds->pipefd[1], STDOUT_FILENO) == -1)
		handle_error(data, "", "Error:\ndup2 failed", 1);
	close(data->fds->prev_pipe);
	close(data->fds->pipefd[1]);
	execve(data->command_path, data->current_command, env);
	free_data(data);
	exit(1);
}

int	handle_last_process(t_data *data, char **env)
{
	errno = 0;
	if (!data->current_command[0])
		handle_error(data, "", "permission denied", 1);
	if (!data->command_path)
	{
		free_data(data);
		exit(127);
	}
	else if (data->fds->prev_pipe < 1)
	{
		free_data(data);
		exit(0);
	}
	if (dup2(data->fds->prev_pipe, STDIN_FILENO) == -1)
		handle_error(data, "", "Error:\ndup2 failed", 1);
	if (dup2(data->fds->outfile, STDOUT_FILENO) == -1)
		handle_error(data, "", "Error:\ndup2 failed", 1);
	close(data->fds->prev_pipe);
	close(data->fds->outfile);
	execve(data->command_path, data->current_command, env);
	free_data(data);
	exit(127);
}
