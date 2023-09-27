#include "shell.h"

/**
 * _atoi - converts a string into an integer
 * @s: a string to be converted
 * Return: integer value
 **/

int _atoi(char *s)
{
unsigned int num = 0;
int sign = 1;

do

{
if (*s == '-')
sign *= -1;
else if (*s >= '0' && *s <= '9')
num = (num * 10) + (*s - '0');
else if (num > 0)
break;
} while (*s++);

return (num *sign);
}

/**
 * _setenv - function to add or modify environment variable
 * @args: array of command line arguments passed to it
 * Return: always 0 on success
**/

int _setenv(char **args)
{
if (args[1] == NULL || args[2] == NULL)
{
return (0);
}
if (setenv(args[1], args[2], 1) == -1)
{
perror("setenv");
return (-1);
}
return (0);
}

/**
 * _unsetenv - function to remove environment variable
 * @args: array of command line arguments passed to it
 * Return: always 0 on success
**/

int _unsetenv(char **args)
{
if (args[1] == NULL)
{
return (0);
}
if (unsetenv(args[1]) == -1)
{
perror("unsetenv");
return (-1);
}
return (0);
}

/**
 * execute_builtin - function to execute builtin commands
 * @args: array of command line arguments passed to it
 * Return: 0 on success or -1 on error
**/

int execute_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(args[0]);
		free(args);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		return (_cd(args));
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		return (_setenv(args));
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		return (_unsetenv(args));
	}
	return (-1);
}


/**
 * _display - display a string
 * @s_dis: string to display
 * Return: void
 **/

void _display(char *s_dis)
{
	write(STDOUT_FILENO, s_dis, _strlen(s_dis));
}
