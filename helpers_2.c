#include "shell.h"

void handleLine(char **line, ssize_t read);
ssize_t getNewLen(char *line);
void logicalOperations(char *line, ssize_t *newLength);

/**
 * handleLine - diviids a line read from STD_IN as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: spaces are inserted to separate between  "&&","||" ,";" and
 *              Replaces "#" with '\0'.
 */
void handleLine(char **line, ssize_t read)
{
	char *oldLine, *newLine;
	char previous, current, next;
	size_t i, j;
	ssize_t newLength;

	newLength = getNewLen(*line);
	if (newLength == read - 1)
		return;
	newLine = malloc(newLength + 1);
	if (!newLine)
		return;
	j = 0;
	oldLine = *line;
	for (i = 0; oldLine[i]; i++)
	{
		current = oldLine[i];
		next = oldLine[i + 1];
		if (i != 0)
		{
			previous = oldLine[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					newLine[j++] = ' ';
					newLine[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					newLine[j++] = ';';
					newLine[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					newLine[j++] = ' ';
				newLine[j++] = ';';
				if (next != ' ')
					newLine[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					newLine[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					newLine[j++] = '&';
					newLine[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					newLine[j++] = ' ';
				else if (previous == '|' && next != ' ')
				{
					newLine[j++] = '|';
					newLine[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && oldLine[i - 1] != ' ')
				newLine[j++] = ' ';
			newLine[j++] = ';';
			if (next != ' ' && next != ';')
				newLine[j++] = ' ';
			continue;
		}
		newLine[j++] = oldLine[i];
	}
	newLine[j] = '\0';

	free(*line);
	*line = newLine;
}

/**
 * getNewLen - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: remove lines containing '#' with '\0'.
 */

ssize_t getNewLen(char *line)
{
	size_t i;
	ssize_t newLength = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					newLength += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					newLength += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					newLength++;
				if (next != ' ')
					newLength++;
			}
			else
				logicalOperations(&line[i], &newLength);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				newLength++;
			if (next != ' ' && next != ';')
				newLength++;
		}
		newLength++;
	}
	return (newLength);
}
/**
 * logicalOperations - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @newLength: Pointer to newLength in getNewLen function.
 */
void logicalOperations(char *line, ssize_t *newLength)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*newLength)++;
		else if (previous == '&' && next != ' ')
			(*newLength)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*newLength)++;
		else if (previous == '|' && next != ' ')
			(*newLength)++;
	}
}
