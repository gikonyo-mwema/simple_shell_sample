#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static size_t buffer_pos = 0;
static size_t buffer_size = 0;

ssize_t custom_getline(int fd, char **line);

static ssize_t read_data(int fd);
static char *create_line_buffer(size_t size);

ssize_t custom_getline(int fd, char **line)
{
	size_t line_size = 0;
	char *line_buffer = NULL;

	if (fd < 0 || line == NULL)
	{
		/* Invalid arguments */
		return (-1);
	}

	if (buffer_pos >= buffer_size && read_data(fd) <= 0)
	{
		return (-1);
	}

	while (buffer_pos < buffer_size)
	{
		char current_char = buffer[buffer_pos++];

		if (current_char == '\n')
		{
			if (line_buffer == NULL)
			{
				line_buffer = create_line_buffer(1);
				if (line_buffer == NULL)
				{
					return (-1);
				}
				line_buffer[0] = '\0';
			}
			else
			{
				line_buffer[line_size] = '\0';
			}

			*line = line_buffer;
			return (line_size);
		}
		else
		{
			char *new_line_buffer = (char *)realloc(line_buffer, line_size + 2);

			if (new_line_buffer == NULL)
			{
				free(line_buffer);
				return (-1);
			}
			line_buffer = new_line_buffer;
			line_buffer[line_size++] = current_char;
		}
	}

	return (custom_getline(fd, line));
			}

			static ssize_t read_data(int fd)
			{
			buffer_size = read(fd, buffer, BUFFER_SIZE);
			return (buffer_size);
			}

			static char *create_line_buffer(size_t size)
			{
			return (char *)malloc(size);
}
