#include "famine.h"

int		check_process(char *name, int pid)
{
	DIR* dir;
	struct dirent* ent;
	char* endptr;
	char buf[512];

	if ((name == NULL || strlen(name) == 0) && pid < 0)
		return (1);

	if (!(dir = opendir("/proc"))) {
		perror("can't open /proc");
		return (-1);
	}

	while ((ent = readdir(dir)) != NULL)
	{
		if (pid > 0 && atoi(ent->d_name) == pid)
			return (0);

		long lpid = strtol(ent->d_name, &endptr, 10);
		if (*endptr != '\0')
			continue;
		snprintf(buf, sizeof(buf), "/proc/%ld/stat", lpid);
		int fd = open(buf, O_RDONLY);

		if (fd >= 0)
		{
			int size;
			if ((size = read(fd, buf, 512)) > 0)
			{
				buf[size - 1] = '\0';
				if (strstr(buf, name) != NULL)
					return (0);
			}
			close(fd);
		}
	}
	return (1);
}

int	check_debuggeur()
{
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0)
	{
		printf("(∩⌐■▾■)⊃━☆ﾟ.\n");
		return (1);
	}
	return (0);
}
