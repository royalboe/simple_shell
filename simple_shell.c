#include "shell.h"

/**
 * create_child - Creates a child process in order to execute another program.
 * @arg: An array of pointers to strings containing the possible name
 * of a program and its parameters. This array is NULL terminated.
 * @input: The contents of the read line.
 * @count: A counter keeping track of how many commands have been entered
 * into the shell.
 * @av: Name of the program running the shell
 */
void create_child(char **arg, char *input, int count, char **av)
{
	int i, isFound, status;
	char *tmp_command, *command;
	struct stat buf;
	pid_t id;

	id = fork();
	if (id == 0)
	{
		tmp_command = arg[0];
		command = path_finder(arg[0]);
		if (command == NULL)
		{
			/*Looking for file in current directory*/
			isFound = stat(tmp_command, &buf);
			if (isFound == -1)
			{
				printing_err(av[0], count, tmp_command);
				print_str(": not found", 0);
				_free(2, input, tmp_command);
				for (i = 1; arg[i]; i++)
					free(arg[i]);
				free(arg);
				exit(100);
			}
			/*file exist in cwd or has full path*/
			command = tmp_command;
		}
		arg[0] = command;
		if (arg[0] != NULL)
		{
			if (execve(arg[0], arg, environ) == -1)
				exec_err(av[0], count, tmp_command);
		}
	}
	else
		wait(&status);
}

/**
 * get_root - Meant to interact with other token functions, and make
 * them more accessible to other parts of the program.
 * @input: A string containing the raw user input.
 * @delim: A constant string containing the desired delimeter to tokenize line.
 * @parts_count: A holder for the amount of tokens in a string.
 * Return: Upon success an array of tokens representing the command. Otherwise
 * returns NULL.
 */
char **get_root(char *input, const char *delim, int parts_count)
{
	char **arg;

	parts_count = count_parts(input, delim);
	if (parts_count == -1)
	{
		free(input);
		return (NULL);
	}
	arg = split(parts_count, input, delim);
	if (arg == NULL)
	{
		free(input);
		return (NULL);
	}

	return (arg);
}

/**
 * split - Separates a string into an array of tokens. DON'T FORGET TO FREE
 * on receiving function when using tokenize.
 * @parts_count: An integer representing the amount of tokens in the array.
 * @input: String that is separated by an specified delimeter
 * @delim: The desired delimeter to separate tokens.
 * Return: Upon success a NULL terminated array of pointer to strings.
 * Otherwise returns NULL.
 */
char **split(int parts_count, char *input, const char *delim)
{
	int i;
	char **buffer;
	char *part, *input_cp;

	input_cp = _strdup(input);
	buffer = malloc(sizeof(char *) * (parts_count + 1));
	if (buffer == NULL)
		return (NULL);
	part = strtok(input_cp, delim);
	for (i = 0; part != NULL; i++)
	{
		buffer[i] = _strdup(part);
		part = strtok(NULL, delim);
	}
	buffer[i] = NULL;
	free(input_cp);
	return (buffer);
}

/**
 * count_parts - Counts tokens in the passed string.
 * @input: String that is separated by an specified delimeter
 * @delim: The desired delimeter to separate tokens.
 * Return: Upon success the total count of the tokens. Otherwise -1.
 */
int count_parts(char *input, const char *delim)
{
	char *str;
	char *part;
	int i;

	str = _strdup(input);
	if (str == NULL)
		return (-1);
	part = strtok(str, delim);
	for (i = 0; part != NULL; i++)
		part = strtok(NULL, delim);
	free(str);
	return (i);
}
