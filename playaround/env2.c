#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static char	*ft_strndup(const char *s, int n)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	word_number(const char *str, char sep)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (str[++i])
		if ((str[i] != sep) && (i == 0 || sep == str[i - 1]))
			count++;
	return (count);
}

static int	word_len(const char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && sep != str[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	j = -1;
	i = -1;
	res = malloc(sizeof(res) * (word_number(s, c) + 1));
	if (res == NULL)
		return (NULL);
	while (s[++i])
	{
		if ((c != s[i]) && (i == 0 || c == s[i - 1]))
		{
			res[++j] = ft_strndup(s + i, word_len(s + i, c));
			if (res[j] == NULL)
			{
				while (--j >= 0)
					free(res[j]);
				free(res);
				return (NULL);
			}
		}
	}
	res[++j] = NULL;
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	if (!s1)
		return (NULL);
	if (!s2)
		return (strdup(s1));
	res = calloc((strlen(s1) + strlen(s2) + 1), sizeof(char));
	if (!res)
		return (NULL);
	strncpy(res, s1, strlen(s1) + 1);
	strncpy(res + strlen(s1), s2, strlen(s2) + 1);
	return (res);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*path;
	char	**path_table;
	char	*correct_dir;
	char	*cmd[2] = {"ls", NULL};
	int		i;

	i = 0;
	while(env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0) // Buscar exactamente "PATH="
		{
			path = env[i] + 5; // Saltar "PATH="
			break;
		}
		i++;
	}
	path_table = ft_split(path, ':');

	i = 0;
	correct_dir = strdup(path_table[i]);
	while (path_table[i])
	{
		correct_dir = ft_strjoin(path_table[i], "/ls");
		if (!access(correct_dir , X_OK))
		{
			execve(correct_dir, cmd, env);
			free(correct_dir);
			break;
		}
		free(correct_dir);
		i++;
	}

}
