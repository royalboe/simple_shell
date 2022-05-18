#include "shell.h"

/**
 * main - Entry point of the program.
 * @ac: The number of parameters passed
 * @av: The name of the program.
 * Return: Always 0.
 */
int main(__attribute__((unused)) int ac, char **av)
{
	char *line;
	size_t size;
	int command_counter;

	command_counter = 0;
	signal(SIGINT, SIG_IGN);
	do {
		command_counter++;
		line = NULL;
		size = 0;
		parse_line(line, size, command_counter, av);

	} while (1);

	return (0);
}

/**
 * parse_line -split the command line
 * @line: A pointer to a string.
 * @size: size of the commands
 * @command_counter: represent how many command are in the line
 * @av: Name of the program running the shell
 */
void parse_line(char *line, size_t size, int command_counter, char **av)
{
	int i;
	ssize_t read_len;
	int token_count;
	char **param_array;
	const char *delim = "\n\t ";

	token_count = 0;
	if (isatty(STDIN_FILENO) == 1)
	write(STDOUT_FILENO, "$ ", 2);
	read_len = getline(&line, &size, stdin);
	if (read_len != -1)
	{
		param_array = get_root(line, delim, token_count);
		if (param_array[0] == NULL)
		{
			_free(2, param_array, line);
			return;
		}
		i = builtin(param_array, line);
		if (i == -1)
			create_child(param_array, line, command_counter, av);
		for (i = 0; param_array[i] != NULL; i++)
			free(param_array[i]);
		_free(2, param_array, line);
	}
	else
		exit_cmd(line);
}
/**
 * path_finder - find the full path of a program.
 * @command: Represents a command. For example ls, clear.
 * Return: an string with the full path of the program.
 */
char *path_finder(char *command)
{
	char *str = "PATH";
	char *constructed;
	char **path_tokens;
	int index;
	char *directory;

	index = find_path(str);
	path_tokens = split_path(index, str);
	if (path_tokens == NULL)
		return (NULL);

	directory = search_dir(path_tokens, command);
	if (directory == NULL)
	{
		_free2(path_tokens);
		return (NULL);
	}

	constructed = build_path(directory, command);
	if (constructed == NULL)
	{
		_free2(path_tokens);
		return (NULL);
	}

	_free2(path_tokens);

	return (constructed);
}

/**
 * find_path - Finds the index of an environmental variable.
 * @str: Environmental variable that needs to be found.
 * Return: Upon success returns the index of the environmental variable.
 * otherwise returns -1.
 */
int find_path(char *str)
{
	int i;
	int len;
	int j;

	len = _strlen(str);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (environ[i][j] != str[j])
				break;
		}
		if (j == len && environ[i][j] == '=')
			return (i);
	}
	return (-1);
}

/**
 * split_path - Separate a string in an array of directories
 * @index: Index  the path in the environment variables.
 * @str: string to separate and tokenize.
 * Return: an array of pointer to strings.
 */
char **split_path(int index, char *str)
{
char *env_var;
	int token_count;
	const char *delim = ":\n";
	char **path_tokens;
	int len;

	len = _strlen(str);
	token_count = 0;
	env_var = environ[index] + (len + 1);
	path_tokens = get_root(env_var, delim, token_count);
	if (path_tokens == NULL)
		return (NULL);
	return (path_tokens);
}
