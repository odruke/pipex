/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:33:20 by odruke-s          #+#    #+#             */
/*   Updated: 2025/02/26 18:45:51 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	int		infile_fd;
	int		read_buff;
	char	buff;
	pid_t	pid;

	read_buff = 0;
	if (ac < 2)
		handle_error("Error:\nWrong number of arguments\n");
	if (!verify_files(av))
		handle_error("Error:\nNo permit to READ/WRITE files\n");
	else
	{
		infile_fd = open(av[1], O_RDONLY);
		if (infile_fd < 0)
			handle_error("Error:\nCouldn't open infile");

		if (pipe(pipe_fd) == - 1)
			handle_error("Error:\nPipe failed\n");

		pid = fork();
		if (pid == -1)
			handle_error("Error:\nFork failed\n");
		/*child handles cmd*/
		if	(!pid)
			handle_child(infile_fd, pipe_fd, env);
		/*parent handles file*/
		close(pipe_fd[1]);
		read_buff = read(pipe_fd[0], &buff, 1);
		while (read_buff)
		{
			write(STDOUT_FILENO, &buff, 1);
			read_buff = read(pipe_fd[0], &buff, 1);
		}
		close(pipe_fd[0]);
		wait(NULL);
	}
}
