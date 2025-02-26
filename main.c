/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:33:20 by odruke-s          #+#    #+#             */
/*   Updated: 2025/02/26 14:22:40 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (ac < 5)
		handle_error("Error:\nWrong number of arguments\n");
	if (!verify_files(av))
		handle_error("Error:\nNo permit to READ/WRITE files\n");
	else
	{
		if (pipe(pipefd) == - 1)
			handle_error("Error:\nPipe failed\n");
		pid = fork();
		if (pid == -1)
			handle_error("Error:\nFork failed\n")
		/*child handles cmd*/
		if	(!pid)
			handle_child(av, pipefd, env);
		/*parent handles file*/
		if (pid)
			handle_parent(av, pipefd, env);
	}
}
