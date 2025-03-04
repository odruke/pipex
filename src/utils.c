/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:34:21 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/01 17:22:56 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	complete_path(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->PATH_table[i])
	{
		temp = data->PATH_table[i];
		data->PATH_table[i] = ft_strjoin(temp, "/");
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
			data->PATH = env[i] + 5;
			break;
		}
		i++;
	}
	if (!data->PATH)
		handle_error(data, "Error:\nPATH not found in environment", 1);
	data->PATH_table = ft_split(data->PATH, ':');
	complete_path(data);
}

void	find_program(t_data *data)
{
	int		i;

	i = 0;
	data->current_command = ft_split(data->cmds[data->n_cmd], ' ');
	if (!data->current_command)
		handle_error(data, "Error:\nsplit command failed", 1);
	while (data->PATH_table[i])
	{
		data->command_path = ft_strjoin(data->PATH_table[i], data->current_command[0]);
		if (!access(data->command_path, X_OK))
			break;
		free(data->command_path);
		data->command_path = NULL;
		i++;
	}
	if (!data->command_path)
		handle_error(data, data->current_command[0], 0);

}