#include "shell.h"

/**
 * input_tokenize - take input from user and tokenize it
 * @prompt: the input given by user
 * @delim: the delimeter
 * Return: array of strings
 **/

char **input_tokenize(char *prompt, char *delim)
{
	char **args;
	int args_count = 0;
	char *prompt_copy = _strdup(prompt), *token;

	if (prompt_copy == NULL)
		return (NULL);
	token = strtok(prompt_copy, delim);

	while (token != NULL)
	{
		args_count++;
		token = strtok(NULL, delim);
	} free(prompt_copy);
	args = malloc((args_count + 1) * sizeof(char *));

	if (args == NULL)
		return (NULL);
	args_count = 0;
	prompt_copy = _strdup(prompt);
	if (prompt_copy == NULL)
	{
		free(args);
		return (NULL);
	}
	token = strtok(prompt_copy, delim);
	while (token != NULL)
	{
		args[args_count] = _strdup(token);
		if (args[args_count] == NULL)
		{
			free_input(args);
			free(prompt_copy);
			return (NULL);
		}
		args_count++;
		token = strtok(NULL, delim);
	}
	args[args_count] = NULL;
	free(prompt_copy);
	return (args);
}

/**
 * execute_non_builtin - execute non builtin functions
 * @args: array of pointers to arguments
 * @envp: array of pointers to environment variables
 * Return: void
 **/

int execute_non_builtin(char **args, char **envp)
{
	int pid;
	int status = -1;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			perror("Execve failed");
			return (-1);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("Wait failed");
			return (-1);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			perror("Error");
			return (-1);
		}
	}
	return (0);
}

/**
 * execute_if_path - execute functions found in PATH
 * @args: array of pointers to arguments
 * @envp: array of pointers to environment variables
 * Return: always 0 on success
 **/

int execute_if_path(char **args, char **envp)
{
int exec_status = -1;
char *path = _getenv("PATH"), *path_copy = _strdup(path), *token, *fileloc;

if (path_copy == NULL)
	perror("Error: failed to duplicate PATH");
token = strtok(path_copy, ":");
while (token != NULL)
{
	fileloc = malloc(_strlen(token) + _strlen(args[0]) + 2);
	if (fileloc == NULL)
	{
	perror("Error: failed to allocate memory");
	free(path_copy);
	} _strcpy(fileloc, token);
	_strcat(fileloc, "/");
	_strcat(fileloc, args[0]);
	if (access(fileloc, X_OK) == 0)
	{
	free(args[0]);
	args[0] = fileloc;
		exec_status = execute_non_builtin(args, envp);
		if (exec_status != 0)
		{
		free(path_copy);
		free(path);
		return (exec_status);
		}
		else
		{
		free(path);
		free(path_copy);
		return (0);
		}
	}
	else
	free(fileloc);
	token = strtok(NULL, ":");
} free(path_copy);
free(path);
return (exec_status);
}

/**
 * handle_input - handles input given by user
 * @prompt: the input entered by user
 * @envp: array of pointers to environment variables
 * Return: always 0 on success
 **/

int handle_input(char *prompt, char **envp)
{
	int i, status;
	char **input = NULL, **args = NULL;

	input = input_tokenize(prompt, "\n");
	for (i = 0; input[i] != NULL; i++)
	{
		args = input_tokenize(input[i], " ");
		if (args[0] != NULL)
		{ status = execute_builtin(args);
			if (status != -1)
			{
				free_input(args);
				free_input(input);
				free(prompt);
				return (status);
			}
				if (access(args[0], X_OK) == 0)
				{
				status = execute_non_builtin(args, envp);
				if (status != -1)
				{
					free_input(args);
					continue;
					return (status);
				}
				} status = execute_if_path(args, envp);
			if (status != -1)
			{
				free_input(args);
				continue;
				return (status);
			}
			else
			_display("Error: command not found\n");
		} free_input(args);
	} free_input(input);
	free(prompt);
	return (0);
}

/**
 * main - Entry point to the program
 * @argc: the number of command line arguments
 * @argv: array of command line arguments
 * @envp: array of environment variables
 * Return: always 0 on success
**/

int main(int argc, char **argv, char **envp)
{
	char *prompt = NULL;
	ssize_t result;
	int status = 0;
	(void)argv;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(1, "$ ", 2);
		}
		result = _getline(&prompt);
		if (result == -1)
		{
			perror("getline error");
			status = -1;
			break;
		}
		else if (result == 0)
		{
			if (isatty(STDIN_FILENO))
			{
				write(1, "\n", 1);
			}
			free(prompt);
			break;
		}
		status = handle_input(prompt, envp);
		if (status != 0)
		{
			break;
		}
	}
	return (status);
}

