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


/**
 * free_all - A function to free all memory before exit
 * @input: The input given by user after tokenizing
 * @args: The command line arguments passed to it
 * @commands: The commands to be executed
 * @prompt: The prompt given by user before tokenizing
*/

void free_all(char **input, char **args, char **commands, char *prompt)
{
if (input != NULL)
	free_input(input);
if (args != NULL)
	free_input(args);
if (commands != NULL)
	free_input(commands);
if (prompt != NULL)
	free(prompt);
}

/**
 * _strchr - A function to find the first occurrence of c
 * @str: The string passed to function
 * @c: The charachter to find
 * Return: A pointer to the first occurrence of c
 */

char *_strchr(char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str);
	return (NULL);
}

