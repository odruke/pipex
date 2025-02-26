/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:33:20 by odruke-s          #+#    #+#             */
/*   Updated: 2025/02/26 22:02:40 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	init_data(t_data data)
{
	data->PATH = NULL;
	data->PATH_table = NULL;
	data->cmds = NULL;
	data->n_cmd = 0;
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	int		infile_fd;
	int		outfile_fd;
	int		read_buff;
	int		i;
	char	buff;
	t_data	*data;
	pid_t	pid;

	read_buff = 0;
	i = 2;
	if (ac < 5)
		handle_error(data, "Error:\nWrong number of arguments\n");
	else
	{
		/*open infile to read and open or create outfile to write*/
		infile_fd = open(av[1], O_RDONLY);
		if (infile_fd < 0)
			handle_error(data, "Error:\nCouldn't open infile\n");
		outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNK, 0644);
		if (infile_fd < 0)
			handle_error(data, "Error:\nCouldn't open/create outfile\n");
		/*parsing cmds*/
		init_data(data);
		parsing(data, ac, av, env);
		while (i < ac)
		{
			if (pipe(pipe_fd) == -1)
				handle_error(data, "Error:\nPipe failed\n");

			pid = fork();
			if (pid == -1)
				handle_error(data, "Error:\nFork failed\n");
			/*child handles cmd*/
			if	(!pid)
				handle_procesess(data, infile_fd, pipe_fd);
			data->n_cmd++;
		}
		/*parent handles file*/
		close(pipe_fd[1]);
		read_buff = read(pipe_fd[0], &buff, 1);
		while (read_buff)
		{
			write(outfile_fd, &buff, 1);
			read_buff = read(pipe_fd[0], &buff, 1);
		}
		close(pipe_fd[0]);
		wait(NULL);
	}
}
