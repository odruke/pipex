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
	if (data->fds)
		free(data->fds);
	if (data)
		free(data);
	exit(errno);
}

int	cmd_failed(int exit_code, t_data *data)
{
	(void)data;
	ft_printf("cmd n:%i had error ->%i<-\n", (data->n_cmd + 1), exit_code);
	perror("Error:\ncmd failed");
	return (exit_code);
}

void	handle_error(t_data *data, char *msg)
{
	perror(msg);
	free_and_exit(data);
}