/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:34:21 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/11 20:21:00 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_and_status(t_data *data)
{
	int	exit_code;
	int	child_exit;

	exit_code = 0;
	data->n_cmd++;
	while (data->n_cmd--)
	{
		if (waitpid(-1, &data->status, 0) > 0)
		{
			if (WIFEXITED(data->status))
			{
				child_exit = WEXITSTATUS(data->status);
				if (child_exit != 0)
					exit_code = child_exit;
			}
			else if (WIFSIGNALED(data->status))
				exit_code = 127;
		}
	}
	free_data(data);
	return (exit_code);
}

void	complete_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->path_table[i])
	{
		temp = data->path_table[i];
		data->path_table[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
}

int	cmd_if_absolute_path(t_data *data)
{
	errno = 0;
	data->command_path = ft_strdup(data->current_command[0]);
	if (!access(data->command_path, X_OK))
		return (0);
	else
		return (1);
}

void	reset_current_command(t_data *data)
{
	free_table(data->current_command);
	free(data->command_path);
	data->current_command = NULL;
	data->command_path = NULL;
	data->status = 0;
}
