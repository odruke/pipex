#include "pipex.h"

void handle_procesess(t_data *data, char **env)
{
	close(data->fds->pipefd[0]);
	if (dup2(data->fds->prev_pipe, STDIN_FILENO) == -1)
		handle_error(data, "Error:\ndup2 failed");
	if (dup2(data->fds->pipefd[1], STDOUT_FILENO) == -1)
		handle_error(data, "Error:\ndup2 failed");
	close(data->fds->prev_pipe);
	close(data->fds->pipefd[1]);
	find_program(data);
	if (execve(data->command_path, data->current_command, env) == -1)
		handle_error(data, "Error:\nexecve failed");
	
}

void handle_last_process(t_data *data, char **env)
{
	if (dup2(data->fds->prev_pipe, STDIN_FILENO) == -1)
		handle_error(data, "Error:\ndup2 failed");
	if (dup2(data->fds->outfile, STDOUT_FILENO) == -1)
		handle_error(data, "Error:\ndup2 failed");
	close(data->fds->prev_pipe);
	close(data->fds->outfile);
	find_program(data);
	if (execve(data->command_path, data->current_command, env) == -1)
		handle_error(data, "Error:\nLast execve failed");
}