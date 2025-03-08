/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:34:21 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/06 20:45:48 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		handle_error(data, "Error:\nPATH not found in environment", 1);
	data->path_table = ft_split(data->path, ':');
	complete_path(data);
}
/*
void	parse_current_command(t_data *data, char *cmd)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	data->current_command = (char **)malloc(sizeof(char) * 3);
	if (!data->current_command)
		handle_error(data, "error:\nmalloc failed", 1);
	while (cmd[j] && cmd[j] == ' ')
		j++;
	while (cmd[i + j] && cmd[i + j] != ' ')
		i++;
	data->current_command[0] = ft_strndup(cmd + j, i);
	if (cmd[j + i])
	{
		data->current_command[1] = ft_strdup(cmd + (j + i + 1));
		data->current_command[2] = NULL;
	}
	else
		data->current_command[1] = NULL;

}
*/
void	find_program(t_data *data)
{
	int		i;

	i = 0;
	data->current_command = parsing_current_cmd(data->cmds[data->n_cmd]);
	//data->current_command = ft_split(data->cmds[data->n_cmd], ' ');
	if (!data->current_command)
		handle_error(data, "Error:\nsplit command failed", 1);
	while (data->path_table[i])
	{
		data->command_path = ft_strjoin(data->path_table[i],
				data->current_command[0]);
		if (!access(data->command_path, X_OK))
			break ;
		free(data->command_path);
		data->command_path = NULL;
		i++;
	}
	if (!data->command_path)
		handle_error(data, data->current_command[0], 0);

}

void	reset_current_command(t_data *data)
{
	free_table(data->current_command);
	free(data->command_path);
	data->current_command = NULL;
	data->command_path = NULL;
	data->status = 0;
}