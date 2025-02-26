/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:34:21 by odruke-s          #+#    #+#             */
/*   Updated: 2025/02/26 14:22:44 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void	free_and_exit(data);
{
	
}
*/
int	verify_files(char **av)
{
	if (access(av[1], R_OK) != 0 || acces(av[4], R_OK, W_OK) != 0)
		return (0);
	else
		return (1);
}

void	handle_error(char *msg)
{
	perror(msg);
//	free_and_exit(data);
	exit(errno);
}

void handle_child(char **av, int *pipefd, char **env)
{
	close(pipefd[0]);
}

void handle_parent(char **av, int *pipefd, char **env)
{
	close(pipefd[0]);
	open(av[1], RD_ONLY);
	dup2(pipefd[1], STDOUT_FILENO);

}
