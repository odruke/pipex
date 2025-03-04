/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:33:20 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/01 17:33:38 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_data(t_data *data)
{
	data->PATH = NULL;
	data->PATH_table = NULL;
	data->cmds = NULL;
	data->current_command = NULL;
	data->command_path = NULL;
	data->n_cmd = 0;
	data->status = 0;
	data->pid = 0;
	data->fds = ft_calloc(1, sizeof(t_fds));
}

static void	init_fds(t_data *data, int ac, char **av)
{
	data->fds->infile = open(av[1], O_RDONLY);
	if (data->fds->infile < 0)
		handle_error(data, "Error:\nCouldn't open infile");
	data->fds->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fds->infile < 0)
		handle_error(data, "Error:\nCouldn't open/create outfile\n");
	data->fds->prev_pipe = data->fds->infile;
}

static void	cycling_processes(t_data *data, int ac, char **env)
{
	int		i;
	pid_t	pid;

	i = 2;
	while ((ac - 2) > i)
	{
		errno = 0;
		
		if (pipe(data->fds->pipefd) == -1)
			handle_error(data, "Error:\nPipe failed");
		pid = fork();
		
		if (pid == -1)
			handle_error(data, "Error:\nFork failed");
		find_program(data);
		if (!pid)
			handle_procesess(data, env);

		waitpid(-1, &data->status, 0);
	//	if (WIFEXITED(data->status) && WEXITSTATUS(data->status) != 0)
	//		cmd_failed(WEXITSTATUS(data->status), data);
		if (WIFEXITED(data->status))		
		{		
			ft_printf("statud:%i\n", data->status);
			int exit_status = WEXITSTATUS(data->status);  	
						
			if (exit_status != 0)	
			{
				ft_printf("%s %s: command not found\ncódigo: %d\n", data->current_command[0], data->current_command[1] ,exit_status);	
				ft_printf("El comando falló con código de error: %d\n", exit_status);
			}	
			else if (WIFSIGNALED(data->status))
			{
				ft_printf("Proceso hijo terminó por señal: %d\n", WTERMSIG(data->status));	
			}
		}
		free_table(data->current_command);
		free(data->command_path);
		data->current_command = NULL;
		data->command_path = NULL;
		data->status = 0;
		data->n_cmd++;
		close(data->fds->prev_pipe);
		close(data->fds->pipefd[1]);
		data->fds->prev_pipe = data->fds->pipefd[0];
		i++;
	}
}

static void	last_process(t_data *data, char **env)
{
	errno = 0;
	data->pid = fork();
	if (data->pid == -1)
		handle_error(data, "Error:\n2nd fork failed");
	find_program(data);
	if (data->pid == 0)
		handle_last_process(data, env);
	close(data->fds->prev_pipe);
	close(data->fds->outfile);
	close(data->fds->pipefd[0]);
	waitpid(-1, &data->status, 0);
	//if (WIFEXITED(data->status) && WEXITSTATUS(data->status) != 0)
    //	cmd_failed(WEXITSTATUS(data->status), data);
		if (WIFEXITED(data->status))
		{	
			int exit_status = WEXITSTATUS(data->status);	
			if (exit_status != 0)
			{
				perror(data->current_command[0]);
				perror(data->current_command[1]);
				perror(": command not found");
			}
				//ft_printf("%s %s: command not found\ncódigo: %d\n", data->current_command[0], data->current_command[1] ,exit_status);
		}
	free_and_exit(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (ac < 5)
	{
		perror("Error:\nWrong number of arguments");
		exit(errno);
	}
	data = ft_calloc(1, sizeof(t_data));
	init_data(data);
	init_fds(data, ac, av);
	parsing(data, ac, av, env);
	cycling_processes(data, ac, env);
	last_process(data, env);
	return (errno);
}
