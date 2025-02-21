#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid[2];
    int pipefd[2];
    char *path = "example.txt";
    char *commands[4] = {"cat", "-e", path, NULL};
    char *commands2[3] = {"wc", "-w", NULL};

    // Crear el pipe antes de los forks
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (0);
    }

    pid[0] = fork();  // Primer fork para el proceso hijo de cat
    if (pid[0] == -1)
    {
        perror("fork");
        return (0);
    }

    if (pid[0] == 0)
    {
        // En el proceso hijo de cat
        close(pipefd[0]);  // No se necesita leer del pipe
        dup2(pipefd[1], STDOUT_FILENO);  // Redirigir salida estándar al pipe
        execve("/bin/cat", commands, NULL);  // Ejecutar cat
        close(pipefd[1]);  // Cerrar el extremo de escritura después de ejecutar
        return (0);
    }

    pid[1] = fork();  // Segundo fork para el proceso hijo de wc
    if (pid[1] == -1)
    {
        perror("fork");
        return (0);
    }

    if (pid[1] == 0)
    {
        // En el proceso hijo de wc
        close(pipefd[1]);  // No se necesita escribir al pipe
        dup2(pipefd[0], STDIN_FILENO);  // Redirigir entrada estándar desde el pipe
        execve("/bin/wc", commands2, NULL);  // Ejecutar wc
        close(pipefd[0]);  // Cerrar el extremo de lectura después de ejecutar
        return (0);
    }

    // En el proceso padre
    close(pipefd[0]);  // No se necesita leer ni escribir al pipe en el padre
    close(pipefd[1]);

    // Esperar a que ambos procesos hijos terminen
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);

    return (0);
}

