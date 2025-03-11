/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:07:00 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/11 20:19:54 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			data->path = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!data->path)
		data->path = "/";
	data->path_table = ft_split(data->path, ':');
	complete_path(data);
}

void	find_current_cmd(t_data *data)
{
	data->current_command = parsing_current_cmd(data->cmds[data->n_cmd]);
	if (!data->current_command)
		handle_error(data, "", "Error:\nsplit command failed", 1);
}

int	find_program(t_data *data)
{
	int		i;

	i = 0;
	find_current_cmd(data);
	if (ft_strchr(data->current_command[0], '/'))
	{
		if (!cmd_if_absolute_path(data))
			return (0);
		else
			return (handle_error(data,
					data->current_command[0], "directory not found", 0));
	}
	while (data->path_table[i])
	{
		data->command_path = ft_strjoin(data->path_table[i],
				data->current_command[0]);
		if (!access(data->command_path, X_OK))
			return (0);
		free(data->command_path);
		data->command_path = NULL;
		i++;
	}
	return (handle_error(data,
			data->current_command[0], "command not found", 0));
}
