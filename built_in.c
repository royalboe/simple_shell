#include "shell.h"

/**
 * env_cmd - A function that prints all the environmental variables in the current shell.
 * @user_input: A string representing the input from the user.
 */
void env_cmd(__attribute__((unused))char *user_input)
{
	int i;
	int j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * exit_cmd - this exits the shell. After freeing allocated resources.
 * @user_input: A string representing the input from the user.
 */
void exit_cmd(char *user_input)
{
	free(user_input);
	/*print_str("\n", 1);*/
	exit(0);
}

/**
 * check_built_ins - Finds the right function needed for execution.
 * @str: The name of the function that is needed.
 * Return: Upon sucess a pointer to a void function. Otherwise NULL.
 */
void (*check_built_ins(char *str))(char *str)
{
	int i;

	builtin_t buildin[] = {
		{"exit", exit_cmd},
		{"env", env_cmd},
		{NULL, NULL}
	};

	for (i = 0; buildin[i].built != NULL; i++)
	{
		if (_strcmp(str, buildin[i].built) == 0)
		{
			return (buildin[i].f);
		}
	}
	return (NULL);
}

/**
 * builtin - This function checks for builtin functions.
 * @args: An array of all the arguments passed to the shell.
 * @user_input: A string representing the input from the user.
 * Return: If function is found 0. Otherwise -1.
 */
int builtin(char **args, char *user_input)
{
	void (*build)(char *);

	build = check_built_ins(args[0]);
	if (build == NULL)
		return (-1);
	if (_strcmp("exit", args[0]) == 0)
		_free2(command);
	build(user_input);
	return (0);
}
