/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_procesess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:10:49 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/10 12:09:13 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_procesess(t_data *data, char **env)
{
	errno = 0;
	if (data->fds->prev_pipe < 1 || !data->command_path)
	{
		free_data(data);
		exit(errno);
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
	exit(errno);
}

int	handle_last_process(t_data *data, char **env)
{
	errno = 0;
	if (data->fds->prev_pipe < 1 || !data->command_path)
	{
		free_data(data);
		exit(errno);
	}
	if (dup2(data->fds->prev_pipe, STDIN_FILENO) == -1)
		handle_error(data, "", "Error:\ndup2 failed", 1);
	if (dup2(data->fds->outfile, STDOUT_FILENO) == -1)
		handle_error(data, "","Error:\ndup2 failed", 1);
	close(data->fds->prev_pipe);
	close(data->fds->outfile);
	execve(data->command_path, data->current_command, env);
	free_data(data);
	exit(errno);
}
