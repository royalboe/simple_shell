#include "shell.h"

/**
 * search_dir - Function that search through directories in path_tokens for a
 * specific file.
 * @path_parts: A pointer to an array of strings.
 * @command: Represents a command given by the user.
 * Return: On Success a string  Otherwise returns NULL.
 */
char *search_dir(char **path_parts, char *command)
{
	int i = 0;
	char *original_path, *buf;
	size_t size;

	buf = NULL;
	size = 0;
	original_path = getcwd(buf, size);
	if (original_path == NULL)
		return (NULL);
	if (command[0] == '/')
		command = command + 1;
	while (path_parts[i] != NULL && path_parts)
	{
		if (find_the_way(path_parts[i], command) == 1)
		{
			chdir(original_path);
			return (path_parts[i]);
		}
		i++;

	}
	if (chdir(original_path) == -1)
	{
		perror("ERROR!");
		return (NULL);
	}
	free(original_path);
	return (NULL);
}

/**
 * find_the_way - switcht the current directory
 * @dir: Directory to chek the file
 * @comand: Command given by the user.
 * Return: If the comand is found return 1,otherwhise return 0.
 */
int find_the_way(char *dir, char *comand)
{
	char *cwd = NULL;
	int s = 0;
	struct stat stat_buf;

	s = chdir(dir);
	if (s == -1)
	{
		perror("ERROR!");
		return (0);
	}
	s = stat(comand, &stat_buf);
	if (s == 0)
	{
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}

/**
 * build_path - Combines two strings one representing the path directory and
 * one representing the command file.
 * @directory: Represents a directory in the path.
 * @command: Command given by the user.
 * Return: Upon success a string representing the full path of a command.
 * Otherwise NULL.
 */
char *build_path(char *directory, char *command)
{
	int dir_len;
	int command_len;
	int len;

	if (directory == NULL || command == NULL)
		return (NULL);
	dir_len = _strlen(directory) + 1;
	command_len = _strlen(command) + 1;
	len = dir_len + command_len;
	return (join_path(len, directory, command));
}

/**
 * join_path - Joins two strings one representing the path directory and
 * one representing the command file.
 * @len: lenght of path
 * @dir: Represents a directory in the path.
 * @comm: Represents a file in a directory of the path.
 * Return: Upon success a string representing the full path of a command.
 * Otherwise NULL.
 */
char *join_path(int len, char *dir, char *comm)
{
	int i, j;
	char *built;

	built = malloc(sizeof(char) * len);
	if (built == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
	{
		for (j = 0; dir[j] != '\0'; j++, i++)
			built[i] = dir[j];
		built[i] = '/';
		i++;
		for (j = 0; comm[j] != '\0'; j++, i++)
			built[i] = comm[j];
	}
	built[--i] = '\0';
	return (built);
}
/**
 * print_number - Prints an unsigned number
 * @n: unsigned integer to be printed
 * Return: The amount of numbers printed
 */
int print_number(int n)
{
	int div;
	int len;
	unsigned int num;

	div = 1;
	len = 0;

	num = n;

	for (; num / div > 9; )
		div *= 10;

	for (; div != 0; )
	{
		len += _write_char('0' + num / div);
		num %= div;
		div /= 10;
	}

	return (len);
}
