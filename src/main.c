/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:33:20 by odruke-s          #+#    #+#             */
/*   Updated: 2025/02/28 13:38:33 by odruke-s         ###   ########.fr       */
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
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	int		prev_pipefd;
	int		infile_fd;
	int		outfile_fd;
	int		i;
	t_data	*data;
	pid_t	pid;

	i = 2;
	data = ft_calloc(1, sizeof(t_data));
	init_data(data);
	if (ac < 5)
		handle_error(data, "Error:\nWrong number of arguments\n");
	else
	{
		/*open infile to read and open or create outfile to write*/
		infile_fd = open(av[1], O_RDONLY);
		if (infile_fd < 0)
			handle_error(data, "Error:\nCouldn't open infile\n");
		outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		prev_pipefd = infile_fd;
		if (infile_fd < 0)
			handle_error(data, "Error:\nCouldn't open/create outfile\n");
		/*parsing cmds*/
		parsing(data, ac, av, env);
		/*create a process for each cmd*/
		while ((ac - 2) > i)
		{
			if (pipe(pipe_fd) == -1)
				handle_error(data, "Error:\nPipe failed\n");

			pid = fork();
			if (pid == -1)
				handle_error(data, "Error:\nFork failed\n");
			/*child handles cmd*/
			if	(!pid)
				handle_procesess(data, prev_pipefd, pipe_fd, env);
			data->n_cmd++;
			dprintf(STDERR_FILENO, "parent PID %d: infile_fd=%d, pipefd[0]=%d, pipefd[1]=%d\n", getpid(), infile_fd, pipe_fd[0], pipe_fd[1]);
			close(infile_fd);
			close(pipe_fd[1]);
			prev_pipefd = pipe_fd[0];
			dprintf(STDERR_FILENO, "parent PID %d: infile_fd=%d, pipefd[0]=%d, pipefd[1]=%d\n", getpid(), infile_fd, pipe_fd[0], pipe_fd[1]);
			i++;
		}
		/*parent create a process to write file*/
		pid = fork();
		if (pid == -1)
			handle_error(data, "Error:\n2nd fork failed\n");
		if (pid == 0)
		{
			dprintf(STDERR_FILENO, "final child PID %d: infile_fd=%d, pipefd[0]=%d, pipefd[1]=%d\n", getpid(), infile_fd, pipe_fd[0], pipe_fd[1]);
			dup2(infile_fd, STDIN_FILENO);
			dup2(outfile_fd, STDOUT_FILENO);
			dprintf(STDERR_FILENO, "final child PID %d: infile_fd=%d, pipefd[0]=%d, pipefd[1]=%d, outfile_fd=%d\n", getpid(), infile_fd, pipe_fd[0], pipe_fd[1], outfile_fd);
			close(infile_fd);
			close(outfile_fd);
			find_program(data);
			if (execve(data->command_path, data->current_command, env) == -1)
				handle_error(data, "Error:\nLast execve failed\n");
//			ft_printf("reached end, waiting\n");
			exit(errno);
		}
		while(wait(NULL) > 0);
		return (errno);
	}
}
