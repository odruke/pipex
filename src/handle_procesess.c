#include "pipex.h"

int	handle_procesess(t_data *data, char **env)
{
	errno = 0;
	close(data->fds->pipefd[0]);
	if (dup2(data->fds->prev_pipe, STDIN_FILENO) == -1)
		handle_error(data, "Error:\ndup2 failed");
	if (dup2(data->fds->pipefd[1], STDOUT_FILENO) == -1)
		handle_error(data, "Error:\ndup2 failed");
	close(data->fds->prev_pipe);
	close(data->fds->pipefd[1]);
	if (execve(data->command_path, data->current_command, env) == -1)
	{
		ft_printf("errno = %i\n", errno);
		perror("print this\n");
		handle_error(data, "Error:\nexecve failed");
	}
	return (127);	
}

void handle_last_process(t_data *data, char **env)
{
	if (dup2(data->fds->prev_pipe, STDIN_FILENO) == -1)
		handle_error(data, "Error:\ndup2 failed");
	if (dup2(data->fds->outfile, STDOUT_FILENO) == -1)
		handle_error(data, "Error:\ndup2 failed");
	close(data->fds->prev_pipe);
	close(data->fds->outfile);
	execve(data->command_path, data->current_command, env);
	ft_printf("errno = %i\n", errno);
	handle_error(data, "Error:\nLast execve failed");
}