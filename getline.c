#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t _getline(char **linePtr, size_t *linePtrSize, FILE *stream);
void assignLineptr(char **linePtr, size_t *linePtrSize, char *buffer, size_t buffSize);

/**
 * _realloc - reallocates memory block using malloc and free.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *memoryBlock;
	char *ptrCopy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		memoryBlock = malloc(new_size);
		if (memoryBlock == NULL)
			return (NULL);

		return (memoryBlock);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptrCopy = ptr;
	memoryBlock = malloc(sizeof(*ptrCopy) * new_size);
	if (memoryBlock == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = memoryBlock;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptrCopy++;

	free(ptr);
	return (memoryBlock);
}

/**
 * _getline - Reads input from a stream.
 * @linePtr: A buffer to store the input.
 * @linePtrSize: The size of linePtr.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **linePtr, size_t *linePtrSize, FILE *stream)
{
	char c = 'x', *buffer;
	static ssize_t input;
	ssize_t ret;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assignLineptr(linePtr, linePtrSize, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}

/**
 * assignLineptr - Reassigns the linePtr variable for _getline.
 * @linePtr: buffer to store an input string.
 * @linePtrSize: size of linePtr.
 * @buffer: string to assign to linePtr.
 * @buffSize: size of buffer.
 */
void assignLineptr(char **linePtr, size_t *linePtrSize, char *buffer, size_t buffSize)
{
	if (*linePtr == NULL)
	{
		if (buffSize > 120)
			*linePtrSize = buffSize;
		else
			*linePtrSize = 120;
		*linePtr = buffer;
	}
	else if (*linePtrSize < buffSize)
	{
		if (buffSize > 120)
			*linePtrSize = buffSize;
		else
			*linePtrSize = 120;
		*linePtr = buffer;
	}
	else
	{
		_strcpy(*linePtr, buffer);
		free(buffer);
	}
}
