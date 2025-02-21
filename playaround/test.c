#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd;

	fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("where is my example?\n");

	return (0);
}
