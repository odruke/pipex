/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:09:21 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/10 22:56:52 by odruke-s         ###   ########.fr       */
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

void	free_data(t_data *data)
{
	if (data->path_table)
		free_table(data->path_table);
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

int	handle_error(t_data *data, char *cmd, char *msg, int terminate)
{
	if (ft_strnstr(msg, "open", ft_strlen(msg)))
		ft_printf_fd(2, "zsh: %s: %s\n", strerror(errno), cmd);
	else
		ft_printf_fd(2, "zsh: %s: %s\n", msg, cmd);
	if (terminate)
	{
		free_data(data);
		exit(1);
	}
	else
		return (1);
}
