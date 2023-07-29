#include "shell.h"

/**
 * input_buf - chained cmd buffers
 * @info: parameter struct
 * @buf: buffer address
 * @len: len var address
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t lenp = 0;

	if (!*len) /* if nothing is left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIINT, SigintHandler);

#if USE_GETLINE r = _getline(buf, &len_p);
#else r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* removes trailing \n */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	} return (r);
}

/**
 * get_input - gets us line minus newline
 * @info: structure parameter
 *
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* cmd chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
}
