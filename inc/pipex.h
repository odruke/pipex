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

typedef struct s_fds
{
    int pipefd[2];
    int prev_pipe;
    int infile;
    int outfile;
} t_fds;

typedef struct s_data
{
    char    *PATH;
    char    **PATH_table;
    char    **cmds;
    char    **current_command;
    char    *command_path;
    t_fds   *fds;
    int     n_cmd;
    int     status;
    pid_t   pid;
} t_data;

void	handle_error(t_data *data, char *msg);
void	free_and_exit(t_data *data);
void	free_table(char **table);
int 	cmd_failed(int exit_code, t_data *data);
void	parsing(t_data *data, int ac, char **av, char **env);
void    find_program(t_data *data);
int    handle_procesess(t_data *data, char **env);
void    handle_last_process(t_data *data, char **env);
void	complete_path(t_data *data);
#endif
