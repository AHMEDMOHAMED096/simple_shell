#include "shell.h"

/**
 * _getline - read the input from user
 * @text: storing the address of the buffer containing the text
 * Return: the number of characters read
 **/

ssize_t _getline(char **text)
{
ssize_t len = BUFFER_SIZE;
static ssize_t nread;
static char *new_buffer;
char *buffer = malloc(len * sizeof(char));

if (buffer == NULL)
{
perror("buffer");
free(buffer);
return (-1);
}
do

{
nread = read(STDIN_FILENO, buffer, len - 1);
if (nread == -1)
{
perror("Read");
free(buffer);
return (-1);
}
else if (nread == len)
{
new_buffer = _realloc(buffer, len * sizeof(char), len * 2);
if (new_buffer == NULL)
{
perror("New_buffer");
free(buffer);
return (-1);
}
free(buffer);
buffer = new_buffer;
}
buffer[nread] = '\0';
} while (nread > 0 && buffer[nread - 1] != '\n');
*text = buffer;
return (nread);
}



/**
 * _realloc - reallocates a memory block
 * @ptr: void pointer of old buffer size
 * @old_size: size of old buffer
 * @new_size: reallocated size of new buffer
 * Return: void
 **/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *pr;
	unsigned int indx;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		pr = malloc(new_size);
		if (pr == NULL)
			return (NULL);
		return (pr);
	}
	if (new_size > old_size)
	{
		pr = malloc(new_size);
		if (pr == NULL)
			return (NULL);
		for (indx = 0; indx < old_size && indx < new_size; indx++)
			*((char *)pr + indx) = *((char *)ptr + indx);
		free(ptr);
	}
	return (pr);
}

