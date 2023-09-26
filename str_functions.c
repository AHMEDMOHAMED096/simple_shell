#include "shell.h"

/**
 * _strcat - function to concatenates two strings
 * @dest: the destination string
 * @str:  the source string
 * Return: string of the new modified destination string
**/
char *_strcat(char *dest, const char *str)
{
	int len1, len2, i;

	len1 = _strlen(dest);
	len2 = _strlen(str);

	for (i = 0; i <= len2; i++)
	{
		dest[len1 + i] = str[i];
	}
	return (dest);
}

/**
 * _strlen - function to get the length of string
 * @str:  the string to get length from
 * Return: the length of string
**/

size_t _strlen(const char *str)
{
	int len = 0;

	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

/**
 * _strcmp - function to compare between two strings
 * @str1: the first string
 * @str2: the second string
 * Return: 0 if the string are the same or non zero if there is difference
**/

int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return (*str1 - *str2);
}

/**
 * _strdup - function duplicate a string
 * @dup: the string to be duplicated
 * Return: the duplicated string
**/

char *_strdup(const char *dup)
{
	char *ptr;

	char *cpy = malloc((_strlen(dup) + 1) * sizeof(char));

	if (cpy == NULL)
	{
		return (NULL);
	}

	ptr = cpy;
	while (*dup != '\0')
	{
		*ptr++ = *dup++;
	}
	*ptr = '\0';
	return (cpy);
}

/**
 * _strcpy - function to copies the string of cpy
 * @dest: the string to copy to
 * @cpy: the string to copy from
 * Return: the copied string
**/

char *_strcpy(char *dest, const char *cpy)
{
	char *ptr = dest;

	while (*cpy != '\0')
	{
		*dest++ = *cpy++;
	}
	*dest = '\0';
	return (ptr);
}

