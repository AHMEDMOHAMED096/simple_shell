#include "shell.h"

/**
 * _getenv - A function to get the global environment variables
 * @env: The environment variable name passed to the function
 * Return: The environment variable
*/

char *_getenv(const char *env)
{
	int i = 0;
	char *value = NULL;

	while (environ[i] != NULL)
	{
		char *env_var = _strdup(environ[i]);
		char *token = strtok(env_var, "=");

		if (_strcmp(token, env) == 0)
		{
			value = _strdup(strtok(NULL, "="));
			free(env_var);
			break;
		}
		free(env_var);
		i++;
	}
	return (value);
}

/**
 * free_input - A function to free the tokenizing input from user
 * @input: The input given by user
*/
void free_input(char **input)
{
	int i;

	if (input == NULL)
		return;

	for (i = 0; input[i] != NULL; i++)
	{
		free(input[i]);
	}
	free(input);
}

