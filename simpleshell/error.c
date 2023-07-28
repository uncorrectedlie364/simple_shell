#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: Converted number if valid, or -1 on error
 */

int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 *
 * Return: Nothing
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints a decimal (integer) number (base 10)
 * to the given file descriptor
 * @input: the input number
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */

int print_d(int input, int fd)
{
	int count = 0;
	unsigned int _abs_;

	if (input < 0)
	{
		_abs_ = -input;
		count += _putfd('-', fd);
	}
	else
		_abs_ = input;

	if (_abs_ == 0)
		count += _putfd('0', fd);
	else
	{
		char buffer[10];
		int i = 0;

		while (_abs_ > 0)
		{
			buffer[i] = '0' + (_abs_ % 10);
			_abs_ /= 10;
			i++;
		}

		while (i > 0)
		{
			count += _putfd(buffer[i - 1], fd);
			i--;
		}
	}

	return (count);
}

/**
 * convert_number - converter function to convert a number to a string
 * @num: number
 * @base: base (not used in this implementation)
 * @flags: argument flags (not used in this implementation)
 *
 * Return: string representation of the number
 */

char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char *ptr = &buffer[49];
	unsigned long n = num;
	char sign = 0;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	*ptr = '\0';

	do {
		*--ptr = '0' + (n % 10);
		n /= 10;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replaces the first instance of
 * '#' with '\0' in the input buffer
 * @buf: address of the string to modify
 *
 * Return: Nothing
 */

void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
