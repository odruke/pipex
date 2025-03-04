#include "pipex.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}

void	free_data(t_data *data)
{
	if (data->PATH_table)
		free_table(data->PATH_table);
	if (data->cmds)
		free_table(data->cmds);
	if (data->current_command)
		free_table(data->current_command);
	if (data->command_path)
		free(data->command_path);
	if (data->fds)
		free(data->fds);
	if (data)
		free(data);
}

int	cmd_failed(t_data *data)
{
	ft_printf_fd(2, "%s %s: command not found\n", data->current_command[0], data->current_command[1]);
	return (127);//127 provoca doble print??
}

int	handle_error(t_data *data, char *msg, int terminate)
{
	ft_printf_fd(2, "bash: %s: %s\n", msg, strerror(errno));
	if (terminate)
	{
		free_data(data);
		exit(errno);
	}
	else
		return (errno);
}
