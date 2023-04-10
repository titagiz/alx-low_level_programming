#include "main.h"

/**
 * _errexit - print error message and exit
 * @str: err message as string
 * @file: file name as string
 * @code: exit code
 * Return: void
 */
void _errexit(char *str, char *file, int code)
{
	dprintf(STDERR_FILENO, str, file);
	exit(code);
}

/**
 * _cp - copy source file to destination file
 * @file_from: source file
 * @file_to: destination file
 *
 * Return: void
 */
void _cp(char *file_from, char *file_to)
{
	int fd1, fd2, numread, numwrote;
	char buffer[1024];

	fd1 = open(file_from, O_RDONLY);
	if (fd1 == -1)
		_errexit("Error: Can't read from file %s\n", file_from, 98);

	fd2 = open(file_to, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd2 == -1)
		_errexit("Error: Can't write to %s\n", file_to, 99);

	numread = 1024;
	while (numread == 1024)
	{
		numread = read(fd1, buffer, 1024);
		if (numread == -1)
			_errexit("Error: Can't read from file %s\n", file_from, 98);

		numwrote = write(fd2, buffer, numread);

		if (numwrote == -1)
			_errexit("Error: Can't write to %s\n", file_to, 99);
	}

	if (numread == -1)
		_errexit("Error: Can't read from file %s\n", file_from, 98);
	if (close(fd2) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd2);
		exit(100);
	}
	if (close(fd1) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd2);
		exit(100);
	}
}
/**
 *main - copies a file to another file
 *@argc: number of arguments passed to function
 *@argv: array containing arguments
 *Return: 0 on success
 */
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	_cp(argv[1], argv[2]);

	return (0);
}
