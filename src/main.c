/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:33:20 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/11 19:58:56 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_infile(t_data *data, char **av)
{
	data->fds->infile = open(av[1], O_RDONLY);
	if (data->fds->infile < 0)
		handle_error(data, av[1], strerror(errno), 0);
	data->fds->prev_pipe = data->fds->infile;
}

static void	init_outfile(t_data *data, int ac, char **av)
{
	wait(NULL);
	data->fds->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fds->outfile < 0)
	{
		ft_printf_fd(2, "zsh: %s: %s\n", strerror(errno), av[ac - 1]);
		free_data(data);
		exit(1);
	}
}

static void	cycling_processes(t_data *data, int ac, char **env)
{
	int		i;
	pid_t	pid;

	i = 2;
	while ((ac - 2) > i)
	{
		data->status = 0;
		if (pipe(data->fds->pipefd) == -1)
			handle_error(data, "", "Error:\nPipe failed", 1);
		if (data->fds->prev_pipe > 0)
		{
			find_program(data);
			pid = fork();
			if (pid == -1)
				handle_error(data, "", "Error:\nFork failed", 1);
			if (!pid)
				handle_procesess(data, env);
			reset_current_command(data);
		}
		close(data->fds->prev_pipe);
		close(data->fds->pipefd[1]);
		data->fds->prev_pipe = data->fds->pipefd[0];
		data->n_cmd++;
		i++;
	}
}

static void	last_process(t_data *data, char **env)
{
	errno = 0;
	find_program(data);
	data->pid = fork();
	if (data->pid == -1)
		handle_error(data, "", "Error:\n2nd fork failed", 1);
	if (data->pid == 0)
		handle_last_process(data, env);
	close(data->fds->prev_pipe);
	close(data->fds->outfile);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (ac != 5)
	{
		ft_printf_fd(2, "Error: Wrong number of arguments\n");
		exit(EINVAL);
	}
	data = ft_calloc(1, sizeof(t_data));
	init_data(data);
	init_infile(data, av);
	parsing(data, ac, av, env);
	cycling_processes(data, ac, env);
	init_outfile(data, ac, av);
	last_process(data, env);
	return (wait_and_status(data));
}
