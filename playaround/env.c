#include <stdio.h>

int main(int argc, char **argv, char **env)
{
    int i = 0;
    while (env[i]) // Mientras haya variables de entorno
    {
        printf("%s\n", env[i]); // Imprime cada variable en formato "NOMBRE=VALOR"
        i++;
    }
    return (0);
}

