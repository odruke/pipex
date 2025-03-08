/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:30:59 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/06 22:43:35 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "ft_printf.h"
# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_parsing {
	int		len;
	int		i;
	int		j;
	int		count;
}	t_parsing;

typedef struct s_fds
{
	int	pipefd[2];
	int	prev_pipe;
	int	infile;
	int	outfile;
}	t_fds;

typedef struct s_data
{
	char	*path;
	char	**path_table;
	char	**cmds;
	char	**current_command;
	char	*command_path;
	t_fds	*fds;
	int		n_cmd;
	int		status;
	pid_t	pid;
}	t_data;

int		handle_error(t_data *data, char *msg, int terminate);
void	free_data(t_data *data);
void	free_table(char **table);
void	reset_current_command(t_data *data);
void	parsing(t_data *data, int ac, char **av, char **env);
void	find_program(t_data *data);
int		handle_procesess(t_data *data, char **env);
int		handle_last_process(t_data *data, char **env);
void	complete_path(t_data *data);
char	**ft_split_cmd(char const *s, char c);
char	**parsing_current_cmd(const char *str);
void	space_case(char *str, char **res, t_parsing *tab);
void	double_quota(char *str, char **res, t_parsing *tab);
void	single_quota(char *str, char **res, t_parsing *tab);
int	ft_tab_len(char const *s, char c, int i);

#endif
