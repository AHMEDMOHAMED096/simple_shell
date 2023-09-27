#include "shell.h"

/**
 * get_new_dir - A function to get new directory according to input
 * @args: The new directory path passed to function
 * Return: The new directory path
*/

char *get_new_dir(char **args)
{
	char *new_dir;
	char *dir;

	if (args[1] == NULL)
	{
		new_dir = _getenv("HOME");
	}

	else if (_strcmp(args[1], "-") == 0 || _strcmp(args[1], "..") == 0)
	{
		new_dir = _getenv("OLDPWD");
	}

	else
	{
		return (args[1]);
	}
	dir = _strdup(new_dir);
	free(new_dir);
	return (dir);
}

/**
 * update_env - A function to update env after changing directory
 * @env_var: The env is to be updated
 * @value: The new value of env
 * Return: 0 on success or -1 on error
*/

int update_env(char *env_var, char *value)
{
	if (setenv(env_var, value, 1) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

/**
 * change_dir - A function to change directory
 * @new_dir: The new directory to be changed to
 * Return: 0 on success or -1 on error
*/

int change_dir(char *new_dir)
{
	if (chdir(new_dir) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

/**
 * _cd - A function to handle process of changing directory
 * @args: The new directory path passed to function
 * Return: 0 on success or -1 on error
*/

int _cd(char **args)
{
	char *current_dir, *old_dir, *new_dir = get_new_dir(args);

	if (new_dir == NULL)
	{
		perror("No directory");
		return (-1);
	}
	old_dir = getcwd(NULL, 0);
	if (old_dir == NULL)
	{
		free(new_dir);
		return (-1);
	}
	if (change_dir(new_dir) != 0)
	{
	free(old_dir);
	return (-1);
	}
	if (update_env("OLDPWD", old_dir) != 0)
	{
	free(old_dir);
	free(new_dir);
	return (-1);
	}
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL || update_env("PWD", current_dir) != 0)
	{
	free(old_dir);
	free(new_dir);
	return (-1);
	}
	free(old_dir);
	free(current_dir);
	free(new_dir);
	return (0);
}
