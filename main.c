#include "main.h"

/**
 * main - Simple shell function
 *
 * Return: nothing as it exits when nessesary
 */
int main(void)
{
	ssize_t read_chars;
	size_t len;
	pid_t pid;
	char *argv[2] = {NULL, NULL}, *prompt = NULL;

	while (TRUE)
	{
		_puts("$ ");
		read_chars = getline(&prompt, &len, stdin);
		if (read_chars == -1)
		{
			free(prompt);
			_putchar('\n');
			exit(0);
		}
		prompt[read_chars - 1] = '\0';
		argv[0] = prompt;
		pid = fork();
		if (pid == 0)
		{
			if (execve(prompt, argv, environ) == -1)
			{
				free(prompt);
				perror("hsh: 1:");
				continue;
			}
		}
		else if (pid < 0)
		{
			free(prompt);
			perror("./hsh: 1: Not found\n");
			continue;
		}
		else
		{
			wait(NULL);
			fflush(stdout);
		}
	}
	free(prompt);
	return (0);
}
