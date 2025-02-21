#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	main()
{
	pid_t pid[2];
	int	pipefd[2];
	char	*path;
	path = "example.txt";
	char	*commands[4] = {"cat", "-e", path, NULL};
	char	*commands2[3] = {"wc", "-w", NULL};



	pipe(pipefd);
	pid[0] = fork();
	if (pid[0] == - 1)
		return (0);
	/*proceso hijo*/
	if (pid[0] == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execve("/bin/cat", commands, NULL);
		close(pipefd[1]);
		return (0);
	}
	pid[1] = fork();
	if (pid[1] == - 1)
		return (0);
	if (pid[1] == 0)
		 
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		execve("/bin/wc", commands2, NULL);
		close(pipefd[0]);
		return (0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
