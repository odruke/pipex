#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av)
{	
	if (ac == 2)
	{
		execve("/bin/ls", (*av), NULL);
		printf("This line will not be executed.\n");
	}
	perror("execve");
	return (0);
}
