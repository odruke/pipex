/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:30:59 by odruke-s          #+#    #+#             */
/*   Updated: 2025/02/26 17:56:51 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "ft_printf.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_data
{
    char    *PATH;
    char    *PATH_table;
    char    **cmds;
    int     n_cmd;
} t_data;

void	handle_error(t_data *data, char *msg);
void	free_and_exit(data);
void	parsing(t_data *data, char **av, char **env);
int		verify_files(char **av);
void handle_procesess(t_data data, int infile_fd, int *pipefd);
#endif
